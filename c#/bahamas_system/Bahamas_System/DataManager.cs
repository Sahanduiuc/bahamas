using System;
using System.Collections.Generic;
using System.IO;
using bahamas_system.Bahamas_System.GE;
using bahamas_system.Bahamas_System.GE.Operators.Functions;

namespace bahamas_system.Bahamas_System
{
    public static class DataManager
    {
        public static Dictionary<string,List<string[]>> EquityTimeData = 
            new Dictionary<string, List<string[]>>();

        public static void LoadDataForSymbol(string ticker)
        {
            string curDir = Directory.GetCurrentDirectory();
            string fileName = curDir + @"\msft.csv";
            List<string[]> parsedData = ParseCSV(fileName);

            EquityTimeData.Add("msft",parsedData);
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
    }
}
