using System;
using System.Collections.ObjectModel;

namespace bahamas_system.Bahamas_System
{
    public struct Position
    {
        public string Ticker;
        public float PutPrice;
        public DateTime PutTimestamp;
        public int Units;
    }

    public static class PortfolioManager
    {
        public static Collection<Position> OpenPositions;
        public static float StartingCapital = 10000;
        public static float Capital = StartingCapital;

        public static void ResetPortfolio()
        {
            StartingCapital = 10000;
            Capital = StartingCapital;
            OpenPositions.Clear();
        }
    }
}
