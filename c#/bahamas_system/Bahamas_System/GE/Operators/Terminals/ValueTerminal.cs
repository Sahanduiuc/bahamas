namespace bahamas_system.Bahamas_System.GE.Operators.Terminals
{
    public class ValueTerminal: Terminal
    {
        public float ReturnValue { get; set; }

        public ValueTerminal(float value)
        {
            this.ReturnValue = value;
        }

        public override void Evaluate(int delta)
        {
            ExpressionResult result = new ExpressionResult();
            result.ValueResult = ReturnValue;
            StrategyManager.ResultsStack.Push(result);
        }
    }
}
