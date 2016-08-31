namespace bahamas_system.Bahamas_System.GE.Operators
{
    public struct ExpressionResult
    {
        public bool BinaryResult;
        public double ValueResult;
    }

    public abstract class Operator
    {
        public Operator LeftOperator;
        public Operator RightOperator;

        public abstract ExpressionResult Evaluate();
    }
}
