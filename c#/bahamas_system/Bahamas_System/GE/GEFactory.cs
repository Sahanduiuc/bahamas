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
        private Node targetNode;
        private Dictionary<Type, Action> handlingFunctions;

        public GEFactory()
        {
            handlingFunctions = new Dictionary<Type, Action>
            {
                {typeof(SimpleAdd<Double>),TypeSimpleFunction},
                {typeof(SimpleMul),TypeSimpleFunction},
                {typeof(SimpleDiv),TypeSimpleFunction},
                {typeof(SimpleSub),TypeSimpleFunction}
            };
        }

        /// <summary>
        /// Creates the left and right subnodes of a given node
        /// </summary>
        /// <param name="targetNode"></param>
        public void SetUpNode(Node targetNode)
        {
            this.targetNode = targetNode;
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

        private IOperator GetRandFunction()
        {
            return null;
        }

        private IOperator GetRandVarTerminal()
        {
            return null;
        }

        /// <summary>
        /// Creates a ValueTerminal with a random double value assigned
        /// Value range between MAX and MIN defined
        /// </summary>
        /// <returns></returns>
        private IOperator GetRandValTerminal(double MAX,double MIN)
        {
            return null;
        }
    }
}
