using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;

namespace BahamasEngine
{
    public sealed class MetaDataManager
    {
        public static Dictionary<string, OptionContract> OptionContracts { get; private set; }
        public static Dictionary<string, OptionChainSnapshot>[] OptionChainHistory { get; private set; }
        public static Dictionary<string, OptionChain> OptionChains { get; private set; }
        public static string[] TradingDates { get; private set; }

        private MetaDataManager(){}

        public static void ImportMetaData(string ticker)
        {
            OptionContracts = new Dictionary<string, OptionContract>();
            OptionChains = new Dictionary<string, OptionChain>();

            Console.WriteLine("Starting data load...");
            TradingDates = File.ReadAllLines(Settings.DataPath + $@"{ticker}\" + "TRADINGDATES.txt");

            Console.WriteLine("     Loading Contract MetaData");
            ImportOptionMetaData(ticker);

            Console.WriteLine("     Loading data complete.");
        }

        private static void ImportOptionMetaData(string ticker)
        {
            OptionChainHistory = new Dictionary<string, OptionChainSnapshot>[TradingDates.Length];
            for (int dateIndex = 0; dateIndex < TradingDates.Length; dateIndex++)
            {
                OptionChainHistory[dateIndex] = new Dictionary<string, OptionChainSnapshot>();

                string date = TradingDates[dateIndex];
                var manifestData = File.ReadAllText(Settings.DataPath + $@"{ticker}\" + "MANIFEST_" + date + ".csv").Split('\n');

                foreach (var line in manifestData)
                {
                    string[] rowData = line.Split(',');
                    if (rowData.Length < 5)
                        continue;

                    char type = rowData[4][0];
                    double strike = Convert.ToDouble(rowData[5]);
                    string chainId = rowData[0];
                    string optionId = rowData[1];

                    OptionChain chain = new OptionChain(chainId, Settings.Ticker, rowData[2], rowData[3], 100);
                    OptionChainSnapshot chainSnapshot = new OptionChainSnapshot(chain);
                    OptionContract contract = new OptionContract(optionId, Settings.Ticker, rowData[2], rowData[3], strike, type, chainId);

                    if (!OptionChains.ContainsKey(chainId))
                        OptionChains.Add(chainId, chain);

                    if (!OptionContracts.ContainsKey(contract.ID))
                        OptionContracts.Add(contract.ID, contract);

                    if (!OptionChainHistory[dateIndex].ContainsKey(chainId))
                        OptionChainHistory[dateIndex].Add(chainId, chainSnapshot);

                    OptionChainSnapshot targetchain = OptionChainHistory[dateIndex][chainId];

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
    }
}
