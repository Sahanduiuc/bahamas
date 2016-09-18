using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace bahamas_system.Bahamas_System.GE.Operators.Functions
{
    public struct Position
    {
        public string Ticker;
        public float PutPrice;
        public int Units;
    }

    public static class PortfolioManager
    {
        public static Collection<Position> OpenPositions;
    }
}
