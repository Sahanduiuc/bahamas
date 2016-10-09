using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;

namespace bahamas_system.Bahamas_System
{
    public static class BackTestManager
    {
        private static int TRADEUNITS = 100;

        /// <summary>
        /// 
        /// </summary>
        public static void EvaluateGeneration()
        {
            Console.WriteLine("");
            Console.WriteLine("Backtesting Generation");

            Collection<Strategy> tempStrategies = new Collection<Strategy>();

            int stratNum = 0;
            foreach (var strategy in StrategyManager.StrategyCollection)
            {
                if (stratNum % 10 == 0)
                    Console.Write(".");

                Strategy tempStrategy = strategy;
                EvaluateStrategy(ref tempStrategy);
                tempStrategies.Add(tempStrategy);

                stratNum++;
            }

             int i, j;
             int N = tempStrategies.Count;

             for (j=1; j<N; j++) {
                for (i=j; i>0; i--) {
                    if (tempStrategies[i].Returns > tempStrategies[i - 1].Returns)
                    {
                        var temporary = tempStrategies[i];
                        tempStrategies[i] = tempStrategies[i-1];
                        tempStrategies[i-1] = temporary;
                    }
                }
             }

            StrategyManager.StrategyCollection = tempStrategies;
        }

        public static void EvaluateStrategy(ref Strategy strategy, 
            bool printTrades = false)
        {
            PortfolioManager.ResetPortfolio();

            int i;
            bool prevEvaluation = false;
            var equityData = DataManager.EquityTimeData["msft"];
            int nCount = equityData.Count;
            //double[] closingPricesArr = new double[nCount - 1];
            for (i = 200; i < nCount - 1; i++)
            {
                //if (i % 100 == 0)
                //    Console.Write(".");

                bool evaluationResult = EvaluateStrategyAtDelta(strategy, i);
                DateTime currentDateTime = DateTime.Parse(equityData[i + 1][0]);
                float currentPrice = float.Parse(equityData[i + 1][6]);

                //Open a new LONG Position
                if (evaluationResult && !prevEvaluation &&
                    !PortfolioManager.OpenPositions.Any())
                {
                    if (printTrades)
                    {
                        Console.Write(equityData[i + 1][0]);
                        Console.WriteLine("     BUY {0} at {1}", "MSFT", currentPrice);
                    }
                    Position position = new Position
                    {
                        Ticker = "MSFT",
                        PutPrice = currentPrice,
                        PutTimestamp = currentDateTime,
                        Units = TRADEUNITS
                    };
                    PortfolioManager.OpenPositions.Add(position);
                    PortfolioManager.Capital -= (TRADEUNITS * currentPrice);
                    strategy.TradeCount++;
                }
                //CLOSE position after expiry
                else if (PortfolioManager.OpenPositions.Any() && !evaluationResult)
                {
                    //TimeSpan elapsedTimeSpan = currentDateTime -
                    //                           PortfolioManager.OpenPositions[0].PutTimestamp;
                    //if (elapsedTimeSpan.Days >= 7)
                    //{
                    //    if (printTrades)
                    //    {
                    //        Console.Write(equityData[i + 1][0]);
                    //        Console.WriteLine("     SELL {0} at {1} (EXPIRY)", "MSFT", currentPrice);
                    //    }

                    //    PortfolioManager.Capital += (TRADEUNITS * currentPrice);
                    //    PortfolioManager.OpenPositions.Clear();
                    //}
                    //else
                    //{
                    //    float priceDifference = currentPrice -
                    //                            PortfolioManager.OpenPositions[0].PutPrice;

                    //    if ((priceDifference * TRADEUNITS) < -10)
                    //    {
                    //        if (printTrades)
                    //        {
                    //            Console.Write(equityData[i + 1][0]);
                    //            Console.WriteLine("     SELL {0} at {1} (STOPLOSS)", "MSFT", currentPrice);
                    //        }
                    //        PortfolioManager.Capital += (TRADEUNITS * currentPrice);
                    //        PortfolioManager.OpenPositions.Clear();
                    //    }
                    //    else if ((priceDifference * TRADEUNITS) >= 100)
                    //    {
                    //        if (printTrades)
                    //        {
                    //            Console.Write(equityData[i + 1][0]);
                    //            Console.WriteLine("     SELL {0} at {1} (TAKEPROFIT)", "MSFT", currentPrice);
                    //        }
                    //        PortfolioManager.Capital += (TRADEUNITS * currentPrice);
                    //        PortfolioManager.OpenPositions.Clear();
                    //    }
                    //}

                    if (printTrades)
                    {
                        Console.Write(equityData[i + 1][0]);
                        Console.WriteLine("     SELL {0} at {1} (FLIP)", "MSFT", currentPrice);
                    }

                    PortfolioManager.Capital += (TRADEUNITS * currentPrice);
                    PortfolioManager.OpenPositions.Clear();
                }
                prevEvaluation = evaluationResult;
            }

            StrategyManager.ResultsStack.Clear();
            //StrategyManager.PrintStrategyPerformace(strategy);

            strategy.Returns = (PortfolioManager.Capital -
                    PortfolioManager.StartingCapital) / PortfolioManager.StartingCapital * 100.0f;
        }

        private static bool EvaluateStrategyAtDelta(Strategy strategy, int delta)
        {
            StrategyManager.CurrentOperatorIndex = 0;

            while (StrategyManager.CurrentOperatorIndex <
                strategy.OperatorList.Count)
            {
                strategy.OperatorList[StrategyManager.CurrentOperatorIndex].
                    Evaluate(delta);

                StrategyManager.CurrentOperatorIndex++;
            }

            return StrategyManager.ResultsStack.Pop().BinaryResult;
        }
    }
}
