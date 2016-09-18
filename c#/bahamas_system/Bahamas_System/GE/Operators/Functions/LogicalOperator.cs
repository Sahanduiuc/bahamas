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
            throw new NotImplementedException();
        }

        public override string ToString()
        {
            throw new NotImplementedException();
        }
    }
}
