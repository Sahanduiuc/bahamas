using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace bahamas_system.Bahamas_System.GE.Operators
{
    public static class StrategyManager
    {
        public static Collection<Operator> OperatorList;
        public static Stack<ExpressionResult> ResultsStack; 

        public static int CurrentOperatorIndex;
    }
}
