using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using bahamas_system.Bahamas_System.GE.Operators;

namespace bahamas_system.Bahamas_System
{
    public struct Strategy
    {
        public Collection<Operator> OperatorList;
        public int[] CodonPattern;

        public int CodonLength;

        public int TradeCount;
        public double Returns;

        public void GetHash()
        {
            
        }

        public void AddTrade()
        {
            TradeCount++;
        }
    }

    public static class StrategyManager
    {
        public static Collection<Strategy> StrategyCollection;
        public static Stack<ExpressionResult> ResultsStack;
        public static int CurrentOperatorIndex;

        public static void PrintStrategyPerformace(Strategy strategy)
        {
            Console.WriteLine("");
            Console.WriteLine("**************Strategy Performance**************");
            Console.WriteLine("Total returns:   {0}", PortfolioManager.Capital -
                                                      PortfolioManager.StartingCapital);
            Console.WriteLine("% returns:       {0}%", (PortfolioManager.Capital -
                                                        PortfolioManager.StartingCapital)/
                                                       PortfolioManager.StartingCapital*100.0f);
            Console.WriteLine("Trade Count:     {0}", strategy.TradeCount);
            Console.WriteLine("************************************************");
        }

        public static void PrintSelectedStrategy(Strategy strategy)
        {
            Console.Write("Strategy: ");
            foreach (var currentOperator in strategy.OperatorList)
            {
                Console.Write(currentOperator.ToString() + " ");
            }
            Console.WriteLine("");
        }
    }
}