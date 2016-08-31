using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using bahamas_system.Bahamas_System.GE.Operators;
using bahamas_system.Bahamas_System.GE.Operators.Functions;

namespace bahamas_system.Bahamas_System.GE
{
    public class GEFactory
    {
        private Operator targetOperator;
        private Dictionary<Type, Action> handlingFunctions;

        public GEFactory()
        {
            handlingFunctions = new Dictionary<Type, Action>
            {
                {typeof(SimpleAdd),TypeSimpleFunction},
                {typeof(SimpleMul),TypeSimpleFunction},
                {typeof(SimpleDiv),TypeSimpleFunction},
                {typeof(SimpleSub),TypeSimpleFunction}
            };
        }

        /// <summary>
        /// Creates the left and right subnodes of a given node
        /// </summary>
        /// <param name="targetOperator"></param>
        public void SetUpOperator(Operator targetOperator)
        {
            this.targetOperator = targetOperator;
            handlingFunctions[targetOperator.GetType()].Invoke();
        }

        /// <summary>
        /// Create the subnodes of a simple function
        /// Permits: Functions(double return)/ValTerminals
        /// </summary>
        private void TypeSimpleFunction()
        {
            //Get rand for Sub-Function vs Terminal
            
        }

        private void TypeTerminal()
        {
            
        }

        private Operator GetRandFunction()
        {
            return null;
        }

        private Operator GetRandVarTerminal()
        {
            return null;
        }

        private Operator GetRandFuncOrVar()
        {
            return null;
        }

        /// <summary>
        /// Creates a ValueTerminal with a random double value assigned
        /// Value range between MAX and MIN defined
        /// </summary>
        /// <returns></returns>
        private Operator GetRandValTerminal(double MAX,double MIN)
        {
            return null;
        }
    }
}
