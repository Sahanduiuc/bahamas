using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;

namespace BahamasEngine
{
    public class OptionDataManager
    {
        private string ticker;
        private string dataPath;
        private InstrumentDataManager dataManager;
        private FuturesDataManager futuresDataManager;
        private OptionPricingHelper pricingHelper;

        public Dictionary<string, OptionContract> OptionContracts { get; private set; }
        public Dictionary<string, OptionChainSnapshot>[] OptionChainHistory { get; private set; }
        public Dictionary<string, OptionChain> OptionChains;

        public OptionDataManager(string ticker, string dataPath,
            InstrumentDataManager dataManager, FuturesDataManager futuresDataManager)
        {
            this.ticker = ticker;
            this.dataPath = dataPath;
            this.dataManager = dataManager;
            this.futuresDataManager = futuresDataManager;

            this.pricingHelper = new OptionPricingHelper();
            this.OptionContracts = new Dictionary<string, OptionContract>();
            this.OptionChains = new Dictionary<string, OptionChain>();
        }

        public OptionDataFrame GetCurrentDataFrame(string contractId, int timeIndex)
        {
            string date = dataManager.GetCurrentTradingDate();
            var contents = File.ReadAllLines(dataPath + @"2017\" + date + @"\LO\" +
                contractId + ".csv");

            string[] targetRow = contents[1].Split(',');
            for (int i = 2; i < contents.Length; i++)
            {
                string[] rowData = contents[i].Split(',');

                if (rowData.Length < 57)
                    continue;

                int rowTimeIndex = GetTimeIndex(rowData[6]);
                if (rowTimeIndex > timeIndex)
                    break;

                targetRow = rowData;
            }

            targetRow = ProcessRow(targetRow);
            double midPrice = (Convert.ToDouble(targetRow[1]) + Convert.ToDouble(targetRow[3])) / 2.0;

            OptionDataFrame dataFrame = new OptionDataFrame
            {
                Ticker = ticker,
                EventDate = date,
                Bid = Convert.ToDouble(targetRow[1]) * 1000.0,
                BidSize = Convert.ToInt32(targetRow[2]),
                Ask = Convert.ToDouble(targetRow[3]) * 1000.0,
                Asksize = Convert.ToInt32(targetRow[4]),
                //Delta = GetOptionDelta(contractId, midPrice)               
            };

            return dataFrame;
        }

        public void LoadOptionsMetaData()
        {
            OptionChainHistory = new Dictionary<string, OptionChainSnapshot>[dataManager.TradingDates.Count];
            for (int dateIndex = 0; dateIndex < dataManager.TradingDates.Count; dateIndex++)
            {
                OptionChainHistory[dateIndex] = new Dictionary<string, OptionChainSnapshot>();

                string date = dataManager.TradingDates[dateIndex];
                var manifestData = File.ReadAllText(dataPath + @"Manifests\" +
                    date + ".csv").Split('\n');

                foreach (var line in manifestData.Skip(1))
                {
                    string[] rowData = line.Split(',');
                    if (rowData.Length < 5)
                        continue;

                    char type = rowData[3][0];
                    double strike = Convert.ToDouble(rowData[4]) / 100.0;

                    OptionChain chain = new OptionChain(rowData[1], ticker, "LO", rowData[2], 1000, dataManager);
                    OptionChainSnapshot chainSnapshot = new OptionChainSnapshot(chain);
                    OptionContract contract = new OptionContract(rowData[0], ticker, "LO", rowData[2], strike, type, rowData[1], dataManager);

                    if (!OptionChains.ContainsKey(rowData[1]))
                        OptionChains.Add(rowData[1], chain);

                    if(!OptionContracts.ContainsKey(contract.ID))
                        OptionContracts.Add(contract.ID, contract);

                    if (!OptionChainHistory[dateIndex].ContainsKey(rowData[1]))
                        OptionChainHistory[dateIndex].Add(rowData[1], chainSnapshot);

                    OptionChainSnapshot targetchain = OptionChainHistory[dateIndex][rowData[1]];
                    
                    if (type == 'C')
                    {
                        targetchain.CallOptionContracts.Add(contract);
                    }
                    else if (type == 'P')
                    {
                        targetchain.PutOptionContracts.Add(contract);
                    }
                    else
                    {
                        throw new InvalidDataException();
                    }
                }
            }
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

        private double GetOptionDelta(string contractId, double optionPrice)
        {
            OHLCVDataFrame futuresData = futuresDataManager.GetCurrentDataFrame(
                GetFuturesContractId(contractId));

            char type = contractId[5];
            double delta = 0.0;
            string chainId = OptionContracts[contractId].ChainId;
            double dte = 103.0 / 365.0;

            if (type == 'C')
            {
                throw new NotImplementedException();
            }
            else if (type == 'P')
            {
                double implVol = pricingHelper.ImpliedVolatility('P', futuresData.Close,
                    OptionContracts[contractId].Strike, 0.00691, dte, optionPrice);
                delta = pricingHelper.PutDelta(futuresData.Close,
                    OptionContracts[contractId].Strike, 0.00691, implVol, dte);
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

        #endregion
    }
}
