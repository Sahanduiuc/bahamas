using Newtonsoft.Json;
using System;
using System.Collections.Generic;

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
        private static readonly string outputDir = @"C:\Users\shami\Desktop\bahamas\ResearchTools\Backtest_Results";
        private static TradeReport report = new TradeReport();

        public static void LogTradeExecution(FillEvent fEvent, 
            InstrumentDataManager dataManager)
        {
                               
        }

        public static void LogSeriesData(string name, double value, string timeStamp)
        {
            if (!report.SeriesData.ContainsKey(name))
                report.SeriesData.Add(name, new List<Tuple<string, double>>());
            report.SeriesData[name].Add(new Tuple<string, double>(timeStamp, value));
        }

        public static void GenerateReport(string reportId)
        {
            string output = JsonConvert.SerializeObject(report);
        }
    }
}
