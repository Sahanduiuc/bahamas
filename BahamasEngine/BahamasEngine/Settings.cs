namespace BahamasEngine
{
    public static class Settings
    {
        public static string Ticker => "SPX";

        public static string DataPath => @"D:\bahamas_data\";

        public static string DateFormat => "yyyyMMdd";

        public static int TimeStartIndex = 600;

        public static int TimeEndIndex = 900;

        public static int TimeStepSize = 5;

        public static double Multiplier = 100.0;

        public static double LIBORRate = 0.00691;
    }
}
