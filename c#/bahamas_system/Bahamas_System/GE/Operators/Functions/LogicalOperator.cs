using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace bahamas_system.Bahamas_System.GE.Operators.Functions
{
    public enum LogicalOperators
    {
        AND,
        OR
    }

    public class LogicalOperator: Function
    {
        private LogicalOperators type;

        public LogicalOperator(LogicalOperators type)
        {
            this.type = type;
        }

        public override void Evaluate(int delta)
        {
            bool bool00 = StrategyManager.ResultsStack.Pop().BinaryResult;
            bool bool01 = StrategyManager.ResultsStack.Pop().BinaryResult;
            ExpressionResult result = new ExpressionResult();
            switch (type)
            {
                case LogicalOperators.AND:
                    result.BinaryResult = bool00 && bool01;
                    break;
                case LogicalOperators.OR:
                    result.BinaryResult = bool00 || bool01;
                    break;
            }
            StrategyManager.ResultsStack.Push(result);
        }

        public override string ToString()
        {
            return type.ToString();
        }
    }
}
