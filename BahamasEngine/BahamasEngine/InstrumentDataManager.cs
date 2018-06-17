using System;
using System.Collections.Generic;
using System.Globalization;
using System.IO;
using System.Linq;

namespace BahamasEngine
{
    public class InstrumentDataManager
    {
        private Queue<TradingEvent> eventsQueue;
        private readonly string ticker;
        private int currentDateIndex;
        private int quoteIndex;
        private string dataPath = @"D:\bahamas_data\";

        private OptionDataManager optionDataManager;
        private FuturesDataManager futuresDataManager;

        public const string DATEFORMAT = "yyyyMMdd";
        public IList<string> TradingDates { get; private set; }

        public InstrumentDataManager(string ticker, ref Queue<TradingEvent> eventsQueue)
        {
            this.ticker = ticker;
            this.eventsQueue = eventsQueue;
            this.currentDateIndex = -1;
            this.quoteIndex = 1080;
            this.dataPath += ticker + @"\";

            this.TradingDates = new List<string>();
            this.futuresDataManager = new FuturesDataManager(ticker, dataPath, this);
            this.optionDataManager = new OptionDataManager(ticker, dataPath, this, futuresDataManager);

            LoadMetaData();
        }

        public void StreamNextEvent()
        {
            GetNextTradingTimeStamp();
            OptionChainUpdateEvent updateEvent = new OptionChainUpdateEvent(ticker);
            
            foreach(var element in optionDataManager.OptionChainHistory[currentDateIndex])
            {
                updateEvent.OptionChains.Add(element.Value);
            }
            eventsQueue.Enqueue(updateEvent);
        }

        public bool EOD()
        {
            if (currentDateIndex == TradingDates.Count - 1)
                return true;
            return false;
        }

        public double GetCurrentPrice(string contractId)
        {
            OptionDataFrame dataFrame = GetCurrentOptionDataFrame(contractId);
            return ((dataFrame.Bid + dataFrame.Ask) / 2.0);
        }

        public OptionDataFrame GetCurrentOptionDataFrame(string contractId)
        {
            return optionDataManager.GetCurrentDataFrame(contractId, quoteIndex);
        }

        public string GetCurrentTradingDate()
        {
            return TradingDates[currentDateIndex];
        }

        public OptionContract GetContractData(string contractId)
        {
            return optionDataManager.OptionContracts[contractId];
        }

        #region Private Methods

        private void LoadMetaData()
        {
            Console.WriteLine("Starting data load...");
            //Load Trading Dates
            var tDayContents = File.ReadAllText(dataPath + "FUT_Continuous.csv").
                Split('\n');
            foreach (var line in tDayContents.Skip(1))
            {
                string date = line.Split(',')[0];
                TradingDates.Add(date);                
            }

            Console.WriteLine("     Loading Futures data");
            futuresDataManager.LoadFuturesData();
            Console.WriteLine("     Loading Contract MetaData");
            optionDataManager.LoadOptionsMetaData();
            Console.WriteLine("     Loading data complete.");
        }

        private void GetNextTradingTimeStamp()
        {
            currentDateIndex++;
        }

#endregion
    }
}
