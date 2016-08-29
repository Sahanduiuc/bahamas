using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace bahamas_system.Bahamas_System.GE.Operators.Functions
{
    public class SimpleAdd<T>: Function
    {
        private readonly double val00;
        private readonly double val01;
        private readonly Node baseNode;

        //public double ReturnValue { get; private set; }

        public SimpleAdd(Node baseNode)
        {
            //TODO Handle setting local vals
        }

        public override void Evaluate()
        {
            baseNode.LeftNode.Operator.Evaluate();
            //ReturnValue = val00 + val01;
        }
    }
}
