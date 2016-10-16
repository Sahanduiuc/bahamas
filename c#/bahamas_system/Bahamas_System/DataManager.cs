using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.IO;
using bahamas_system.Bahamas_System.GE;
using bahamas_system.Bahamas_System.GE.Operators.Functions;

namespace bahamas_system.Bahamas_System
{
    public static class DataManager
    {
        private static readonly Dictionary<string,List<string[]>> equityTimeData = 
            new Dictionary<string, List<string[]>>();
        private static readonly Collection<string> tickerCollection = new Collection<string>()
        {
            "msft",
            "spdr"
        };

        public static Collection<string> TickerCollection { get { return tickerCollection; } } 

        public static void LoadData()
        {
            foreach (var ticker in tickerCollection)
            {
                LoadDataForSymbol(ticker);
            }
        }

        public static List<string[]> GetEquityData(string symbol)
        {
            var equityData = equityTimeData[symbol];
            var resultData = new List<string[]>();

            for (int index = 1; index < equityData.Count; index++)
            {
                var currentIndex = DateTime.Parse(equityData[index][0]);

                if ((currentIndex - BackTester.ENDDATETIME).Days > 0)
                    break;

                if ((currentIndex - BackTester.STARTDATETIME).Days >= 0)
                    resultData.Add(equityData[index]);
            }

            return resultData;
        }

#region Private Methods
        private static void LoadDataForSymbol(string ticker)
        {
            string curDir = Directory.GetCurrentDirectory();
            string fileName = curDir + @"\"+ticker+".csv";
            List<string[]> parsedData = ParseCSV(fileName);

            equityTimeData.Add(ticker,parsedData);
        }

        private static List<string[]> ParseCSV(string path)
        {
            List<string[]> parsedData = new List<string[]>();

            try
            {
                using (StreamReader readFile = new StreamReader(path))
                {
                    string line;
                    string[] row;

                    while ((line = readFile.ReadLine()) != null)
                    {
                        row = line.Split(',');
                        parsedData.Add(row);
                    }
                }
            }
            catch (Exception e)
            {
                Console.WriteLine(e.Message);
            }

            return parsedData;
        }

        //TODO
        private static void ValidateDataSet()
        {
            
        }
#endregion
    }
}
