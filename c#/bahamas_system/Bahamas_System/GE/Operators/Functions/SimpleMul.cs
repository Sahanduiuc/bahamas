using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace bahamas_system.Bahamas_System.GE.Operators.Functions
{
    public class SimpleMul : Function
    {
        private readonly double val00;
        private readonly double val01;
        public double ReturnValue { get; private set; }

        public SimpleMul(double val00, double val01)
        {
            this.val00 = val00;
            this.val01 = val01;
        }

        public override void Evaluate()
        {
            ReturnValue = val00 * val01;
        }
    }
}
