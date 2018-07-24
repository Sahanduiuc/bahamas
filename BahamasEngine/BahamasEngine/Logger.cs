using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Globalization;
using System.IO;

namespace BahamasEngine
{
    public struct TradeEntry
    {
        public string TradeDateTime;
        public string Ticker;
        public int Position;
        public double Price;
        public double Commission;
    }

    public sealed class TradeReport
    {
        public string ReportId { get; set; }

        public List<TradeEntry> TradeEntries { get; set; }

        public Dictionary<string, List<Tuple<string, double>>> SeriesData { get; set; }

        public TradeReport()
        {
            TradeEntries = new List<TradeEntry>();
            SeriesData = new Dictionary<string, List<Tuple<string, double>>>();
        }
    }

    public static class Logger
    {
        private static readonly string outputDir = @"D:\Backtest_Results\";
        private static TradeReport report = new TradeReport();
 
        public static void LogTradeExecution(FillEvent fEvent, 
            InstrumentDataManager dataManager)
        {
                               
        }

        public static void LogSeriesData(string name, double value, 
            string date, int timeIndex)
        {
            if (!report.SeriesData.ContainsKey(name))
                report.SeriesData.Add(name, new List<Tuple<string, double>>());

            string timestamp = GetDateTimeString(date, timeIndex);
            report.SeriesData[name].Add(new Tuple<string, double>(timestamp, value));
        }

        public static void GenerateReport(string reportId)
        {
            string content = JsonConvert.SerializeObject(report);
            string fileName = DateTime.Now.ToFileTime().ToString() + 
                "_" + reportId + ".json";
            File.WriteAllText(outputDir + fileName, content);
        }

        private static string GetDateTimeString(string date, int timeIndex)
        {
            DateTime datetime = DateTime.ParseExact(date, "yyyyMMdd", 
                CultureInfo.InvariantCulture);
            datetime = datetime.AddMinutes(timeIndex);

            return datetime.ToString();
        }
    }
}
