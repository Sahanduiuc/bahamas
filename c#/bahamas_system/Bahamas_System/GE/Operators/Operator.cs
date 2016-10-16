namespace bahamas_system.Bahamas_System.GE.Operators
{
    public struct ExpressionResult
    {
        public bool BinaryResult;
        public float ValueResult;
        public string StringResult;
    }

    public abstract class Operator
    {
        public abstract void Evaluate(int delta);
        public abstract override string ToString();
    }
}
