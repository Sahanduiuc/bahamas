using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace bahamas_system.Bahamas_System.GE.Operators.Functions
{
    public class SimpleAdd: Function
    {
        public SimpleAdd()
        {
            //TODO Handle setting local vals
        }

        public override ExpressionResult Evaluate()
        {
            this.LeftOperator.Evaluate();
            this.RightOperator.Evaluate();
            //ReturnValue = val00 + val01;

            return new ExpressionResult();
        }
    }
}
