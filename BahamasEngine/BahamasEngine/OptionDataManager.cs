using System;
using System.Collections.Concurrent;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Threading.Tasks;

namespace BahamasEngine
{
    public class OptionDataManager
    {
        private string ticker;
        private string dataPath;
        private InstrumentDataManager dataManager;
        private OptionPricingHelper pricingHelper;

        public ConcurrentDictionary<string, string[]> OptionDataCache;

        public OptionDataManager(string ticker, string dataPath,
            InstrumentDataManager dataManager)
        {
            this.ticker = ticker;
            this.dataPath = dataPath;
            this.dataManager = dataManager;
            OptionDataCache = new ConcurrentDictionary<string, string[]>();
            
            this.pricingHelper = new OptionPricingHelper();
        }

        public async Task<OptionDataFrame> GetCurrentDataFrameAsync(string contractId, int timeIndex)
        {
            string date = dataManager.GetCurrentTradingDate();
            int targetIndex = 1;

            string[] contents = null;
            string key = date + "_" + contractId;
            bool exists = OptionDataCache.TryGetValue(key, out contents);

            if (!exists)
            {
                contents = File.ReadAllLines(dataPath + @"OptionData\" + date + @"\" +
                    key + ".csv");
                OptionDataCache.TryAdd(key, contents);
            }

            for (int i = 1; i < contents.Length; i++)
            {
                if (contents[i].Length < 10)
                    continue;

                int rowTimeIndex = Convert.ToInt32(contents[i].Substring(0,3));
                if (rowTimeIndex > timeIndex)
                    break;

                targetIndex = i;
            }

            string[] targetRow = contents[targetIndex].Split(',');

            double bid = Convert.ToDouble(targetRow[1]);
            double ask = Convert.ToDouble(targetRow[3]);

            double midPrice = dataManager.CalculateMidPrice(bid, ask);

            OptionDataFrame dataFrame = new OptionDataFrame
            {
                Ticker = ticker,
                EventDate = date,
                Bid = bid * 100.0,
                BidSize = Convert.ToInt32(targetRow[2]),
                Ask = ask * 100.0,
                Asksize = Convert.ToInt32(targetRow[4]),
                Delta = GetOptionDelta(contractId, midPrice, Convert.ToDouble(targetRow[5]))
            };

            return dataFrame;
        }

        #region Private Methods

        private int GetTimeIndex(string timestring)
        {
            string[] components = timestring.Split(new char[] { ':' }, StringSplitOptions.RemoveEmptyEntries);
            TimeSpan diff = new TimeSpan(Convert.ToInt32(components[0]),
                Convert.ToInt32(components[1]), 0);
            return Convert.ToInt32(diff.TotalMinutes);
        }

        private string[] ProcessRow(string[] row)
        {
            string[] data = new string[17];

            data[0] = row[6]; //TimeBar
            data[1] = row[10]; //OpenBid
            data[2] = row[11]; //OpenBidSize
            data[3] = row[13]; //OpenAsk
            data[4] = row[14]; //OpenAskSize
            data[5] = row[19]; //HighBid
            data[6] = row[20]; //HighBidSize
            data[7] = row[22]; //HighAsk
            data[8] = row[23]; //HighAskSize
            data[9] = row[28]; //LowBid
            data[10] = row[29]; //LowBidSize
            data[11] = row[31]; //LowAsk
            data[12] = row[32]; //LowAskSize
            data[13] = row[37]; //SettleBid
            data[14] = row[38];//SettleBidSize
            data[15] = row[40]; //SettleAsk
            data[16] = row[41]; //SettleAskSize

            for (int i = 1; i < data.Length; i++)
            {
                if (string.IsNullOrEmpty(data[i]))
                {
                    data[i] = "0";
                }
            }

            return data;
        }

        private double GetOptionDelta(string contractId, double optionPrice, 
            double underlyingPrice)
        {
            char type = MetaDataManager.OptionContracts[contractId].Type;
            double delta = 0.0;
            string chainId = MetaDataManager.OptionContracts[contractId].ChainId;
            double dte = MetaDataManager.OptionChains[chainId].GetDte(dataManager) / 365.0;

            if (type == 'C')
            {
                throw new NotImplementedException();
            }
            else if (type == 'P')
            {
                double implVol = pricingHelper.ImpliedVolatility('P', underlyingPrice,
                    MetaDataManager.OptionContracts[contractId].Strike, 0.00691, dte, optionPrice);
                delta = pricingHelper.PutDelta(underlyingPrice,
                    MetaDataManager.OptionContracts[contractId].Strike, 0.00691, implVol, dte);
            }
            else
            {
                throw new InvalidDataException();
            }

            return delta;
        }

        private string GetFuturesContractId(string optionChainId)
        {
            char[] contractId = new char[5];

            contractId[0] = ticker[0];
            contractId[1] = ticker[1];
            contractId[2] = optionChainId[2];
            contractId[3] = '1';
            contractId[4] = optionChainId[3];

            return new string(contractId);
        }

        private string ExtractTimeBarColumn(string line)
        {
            int startIndex = 0;
            int seperatorCount = 1;

            while (seperatorCount >= 0)
            {
                if (line[startIndex] == ',')
                    seperatorCount--;
                startIndex++;
            }

            return line.Substring(startIndex, 3);
        }

        #endregion
    }
}
