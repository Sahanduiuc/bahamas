using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

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
    }
}
