using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using bahamas_system.Bahamas_System.GE.Operators.Functions;

namespace bahamas_system.Bahamas_System.GE.Operators
{
    public static class StrategyManager
    {
        public static Collection<Operator> OperatorList;
        public static Stack<ExpressionResult> ResultsStack;
        public static int TradeCount;

        public static int CurrentOperatorIndex;

        public static void PrintStrategyPerformace()
        {
            Console.WriteLine("");
            Console.WriteLine("**************Strategy Performance**************");
            Console.WriteLine("Total returns:   {0}",PortfolioManager.Capital -
                PortfolioManager.StartingCapital);
            Console.WriteLine("% returns:   {0}%", (PortfolioManager.Capital -
                PortfolioManager.StartingCapital)/PortfolioManager.StartingCapital*100.0f);
            Console.WriteLine("************************************************");
        }

        public static void PrintSelectedStrategy()
        {
            Console.Write("Strategy: ");
            foreach (var currentOperator in OperatorList)
            {
                Console.Write(currentOperator.ToString() + " ");
            }
            Console.WriteLine("");
        }
    }
}
