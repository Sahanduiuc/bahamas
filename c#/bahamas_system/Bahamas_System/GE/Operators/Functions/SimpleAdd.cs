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

        public override ExpressionResult Evaluate(int delta)
        {
            this.LeftOperator.Evaluate(delta);
            this.RightOperator.Evaluate(delta);

            return new ExpressionResult();
        }
    }
}
