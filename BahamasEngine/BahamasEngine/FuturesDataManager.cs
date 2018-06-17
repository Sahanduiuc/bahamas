using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;

namespace BahamasEngine
{
    public class FuturesDataManager
    {
        private string ticker;
        private string dataPath;
        private InstrumentDataManager dataManager;
        private Dictionary<string, Dictionary<string, List<OHLCVDataFrame>>> contractData;

        public FuturesDataManager(string ticker, string dataPath,
            InstrumentDataManager dataManager)
        {
            this.ticker = ticker;
            this.dataPath = dataPath;
            this.dataManager = dataManager;

            this.contractData = new Dictionary<string,
                Dictionary<string, List<OHLCVDataFrame>>>();
        }

        public OHLCVDataFrame GetCurrentDataFrame(string contractId)
        {
            List<OHLCVDataFrame> data = contractData[contractId][
                dataManager.GetCurrentTradingDate()];
            OHLCVDataFrame prevDataFrame = data[0];

            foreach (OHLCVDataFrame dataFrame in data)
            {
                if (dataFrame.TimeIndex > 1080)
                    return prevDataFrame;

                prevDataFrame = dataFrame;
            }
            return prevDataFrame;

            throw new InvalidDataException();
        }

        public void LoadFuturesData()
        {
            var manifestData = File.ReadAllText(dataPath + @"CL_Manifest.csv").Split('\n');

            foreach (string contractData in manifestData.Skip(1))
            {
                string[] data = contractData.Split(',');
                if (data.Length < 3)
                    return;

                LoadContractData(data[0]);
            }
        }

        #region Private Methods

        private void LoadContractData(string fileName)
        {
            var data = File.ReadAllText(dataPath + @"FUT\" + fileName + ".txt").Split('\n');

            foreach (string line in data)
            {
                string[] rowData = line.Split(',');
                if (rowData.Length < 6)
                    continue;

                string date = ConvertDateFormat(rowData[0]);
                int timeIndex = GetTimeIndex(rowData[1]);

                if (!contractData.ContainsKey(fileName))
                    contractData.Add(fileName, new Dictionary<string, List<OHLCVDataFrame>>());

                if (!contractData[fileName].ContainsKey(date))
                    contractData[fileName].Add(date, new List<OHLCVDataFrame>());

                OHLCVDataFrame dataFrame = new OHLCVDataFrame
                {
                    Ticker = fileName,
                    Date = date,
                    TimeIndex = timeIndex,
                    Open = Convert.ToDouble(rowData[2]),
                    High = Convert.ToDouble(rowData[3]),
                    Low = Convert.ToDouble(rowData[4]),
                    Close = Convert.ToDouble(rowData[5]),
                    Volume = Convert.ToInt32(rowData[6])
                };

                contractData[fileName][date].Add(dataFrame);
            }
        }

        private int GetTimeIndex(string timestring)
        {
            string[] components = timestring.Split(new char[] { ':' }, StringSplitOptions.RemoveEmptyEntries);
            TimeSpan diff = new TimeSpan(Convert.ToInt32(components[0]),
                Convert.ToInt32(components[1]), 0);
            return Convert.ToInt32(diff.TotalMinutes);
        }

        private string ConvertDateFormat(string date)
        {
            char[] retDate = new char[8];

            // YEAR
            retDate[0] = date[6];
            retDate[1] = date[7];
            retDate[2] = date[8];
            retDate[3] = date[9];
            // MONTH
            retDate[4] = date[0];
            retDate[5] = date[1];
            // DAY
            retDate[6] = date[3];
            retDate[7] = date[4];

            return new string(retDate);
        }

        #endregion
    }
}
