﻿using System;
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
        private string dataPath = @"D:\bahamas_data\";
        private int timeStepSize = 5;

        private OptionDataManager optionDataManager;
        //private FuturesDataManager futuresDataManager;

        public int TimeStampIndex { get { return timestampIndex; } }
        public const string DATEFORMAT = "yyyyMMdd";
        public string[] TradingDates { get; private set; }

        public InstrumentDataManager(string ticker, Queue<TradingEvent> eventsQueue,
            int startDateIndex = 0, int startTimeIndex = 1080)
        {
            this.ticker = ticker;
            this.eventsQueue = eventsQueue;
            this.currentDateIndex = startDateIndex;
            this.timestampIndex = startTimeIndex - timeStepSize;
            this.dataPath += ticker + @"\";

            this.TradingDates = new string[1];
            this.optionDataManager = new OptionDataManager(ticker, dataPath, this);

            LoadMetaData();
        }

        public void SetTradePeriod(int dateIndex, int timeIndex)
        {
            currentDateIndex = dateIndex;
            timestampIndex = timeIndex - timeStepSize;
            OptionDataManager.OptionData = new ConcurrentDictionary<string, string[]>();
        }

        public void StreamNextEvent()
        {
            GetNextTradingTimeStamp();
            OptionChainUpdateEvent updateEvent = new OptionChainUpdateEvent(ticker);

            foreach (var element in optionDataManager.OptionChainHistory[currentDateIndex])
            {
                updateEvent.OptionChains.Add(element.Value);
            }
            eventsQueue.Enqueue(updateEvent);
        }

        public bool EOD()
        {
            if (currentDateIndex == TradingDates.Length - 1)
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
            return TradingDates[currentDateIndex];
        }

        public OptionContract GetContractData(string contractId)
        {
            return optionDataManager.OptionContracts[contractId];
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

        private void LoadMetaData()
        {
            Console.WriteLine("Starting data load...");
            //Load Trading Dates
            TradingDates = File.ReadAllLines(dataPath + "TRADINGDATES.txt");

            //Console.WriteLine("     Loading Futures data");
            //futuresDataManager.LoadFuturesData();
            Console.WriteLine("     Loading Contract MetaData");
            optionDataManager.LoadOptionsMetaData();
            Console.WriteLine("     Loading data complete.");
        }

        private void GetNextTradingTimeStamp()
        {
            timestampIndex+=timeStepSize;
            if (timestampIndex > 600)
            {
                timestampIndex = 600;
                currentDateIndex++;
            }              
        }

        #endregion
    }
}
