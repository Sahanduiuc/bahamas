namespace bahamas_system.Bahamas_System.GE.Operators.Functions
{
    public abstract class Function: Operator
    {
        public abstract override ExpressionResult Evaluate(int delta);
    }
}
