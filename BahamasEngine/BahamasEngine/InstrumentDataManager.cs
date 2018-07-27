using System;
using System.Collections.Concurrent;
using System.Collections.Generic;
using System.Globalization;
using System.IO;
using System.Linq;
using System.Threading.Tasks;

namespace BahamasEngine
{
    public class InstrumentDataManager
    {
        private Queue<TradingEvent> eventsQueue;
        private readonly string ticker;
        private int currentDateIndex;
        private int timestampIndex;
        private string dataPath = Settings.DataPath;
        private int timeStepSize = 5;

        public static readonly int TIMESTARTINDEX = 600;
        public static readonly int TIMEENDINDEX = 900;

        private OptionDataManager optionDataManager;
        //private FuturesDataManager futuresDataManager;

        public int TimeStampIndex { get { return timestampIndex; } }
        public const string DATEFORMAT = "yyyyMMdd";

        public InstrumentDataManager(string ticker, Queue<TradingEvent> eventsQueue,
            int startDateIndex, int startTimeIndex)
        {
            this.ticker = ticker;
            this.eventsQueue = eventsQueue;
            this.currentDateIndex = startDateIndex;
            this.timestampIndex = startTimeIndex - timeStepSize;
            this.dataPath += ticker + @"\";

            this.optionDataManager = new OptionDataManager(ticker, dataPath, this);
        }

        public void StreamNextEvent()
        {
            GetNextTradingTimeStamp();
            OptionChainUpdateEvent updateEvent = new OptionChainUpdateEvent(ticker);

            foreach (var element in MetaDataManager.OptionChainHistory[currentDateIndex])
            {
                updateEvent.OptionChains.Add(element.Value);
            }
            eventsQueue.Enqueue(updateEvent);
        }

        public bool EOD()
        {
            if (currentDateIndex == MetaDataManager.TradingDates.Length - 1)
                return true;
            return false;
        }

        public double GetCurrentPrice(string contractId)
        {
            OptionDataFrame dataFrame = GetCurrentOptionDataFrameAsync(contractId).ConfigureAwait(false).GetAwaiter().GetResult();
            return CalculateMidPrice(dataFrame.Bid, dataFrame.Ask);
        }

        public async Task<OptionDataFrame> GetCurrentOptionDataFrameAsync(string contractId)
        {
            return await optionDataManager.GetCurrentDataFrameAsync(contractId, timestampIndex);
        }

        public string GetCurrentTradingDate()
        {
            return MetaDataManager.TradingDates[currentDateIndex];
        }

        public OptionContract GetContractData(string contractId)
        {
            return MetaDataManager.OptionContracts[contractId];
        }

        public double CalculateMidPrice(double bid, double ask)
        {
            return (bid + ask) / 2.0;

            double midPrice = 0.0;
            if (bid != 0.0 && ask != 0.0)
            {
                midPrice = (bid + ask) / 2.0;
            }
            else if (bid == 0.0)
            {
                midPrice = ask;
            }
            else if (ask == 0.0)
            {
                midPrice = bid;
            }
            return midPrice;
        }

        #region Private Methods

        private void GetNextTradingTimeStamp()
        {
            timestampIndex+=timeStepSize;
            if (timestampIndex > TIMEENDINDEX)
            {
                timestampIndex = TIMESTARTINDEX;
                currentDateIndex++;
            }              
        }

        #endregion
    }
}
