namespace bahamas_system.Bahamas_System.GE.Operators.Terminals
{
    public class ValueTerminal: Terminal
    {
        public double ReturnValue { get; set; }

        public override ExpressionResult Evaluate(){ return new ExpressionResult(); }
    }
}
