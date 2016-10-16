using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace bahamas_system.Bahamas_System.GE.Operators.Terminals
{
    public class StringTerminal : Terminal
    {
        private readonly string returnValue;

        public StringTerminal(string value)
        {
            returnValue = value;
        }

        public override void Evaluate(int delta)
        {
            ExpressionResult result = new ExpressionResult();
            result.StringResult = returnValue;
            StrategyManager.ResultsStack.Push(result);
        }

        public override string ToString()
        {
            return returnValue;
        }
    }
}
