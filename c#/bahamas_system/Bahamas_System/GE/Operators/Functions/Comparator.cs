using System;

namespace bahamas_system.Bahamas_System.GE.Operators.Functions
{
    public enum ComparatorType
    {
        GRTE,
        LSTE
    }

    public class Comparator: Function
    {
        private ComparatorType type;

        public Comparator(ComparatorType type)
        {
            this.type = type;
        }

        public override void Evaluate(int delta)
        {
            float val00 = StrategyManager.ResultsStack.Pop().ValueResult;
            float val01 = StrategyManager.ResultsStack.Pop().ValueResult;
            ExpressionResult result = new ExpressionResult();
            switch (type)
            {
                case ComparatorType.GRTE:
                    result.BinaryResult = val01 >= val00;
                    break;
                case ComparatorType.LSTE:
                    result.BinaryResult = val01 <= val00;
                    break;
            }

            StrategyManager.ResultsStack.Push(result);
        }
    }
}
