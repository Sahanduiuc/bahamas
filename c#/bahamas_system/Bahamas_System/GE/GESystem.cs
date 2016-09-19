using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.IO;
using System.Linq;
using System.Runtime.Remoting.Messaging;
using System.Text;
using System.Threading.Tasks;
using bahamas_system.Bahamas_System.GE.Operators;
using bahamas_system.Bahamas_System.GE.Operators.Functions;
using bahamas_system.Bahamas_System.GE.Operators.Terminals;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;

namespace bahamas_system.Bahamas_System.GE
{
    public class GESystem
    {
        public double MutationRate;
        public double CrossOverRate;
        public UInt16 MaxPoolSize;
        public UInt16 MaxGenerations;
        public UInt16 MaxTreeSize;

        private List<Operator> generationResults;
        private GEFactory factory;
        private Dictionary<string, List<LinkedList<string>>> geGrammar;

        //TODO Portfolio Manager Implementation
        private bool prevEvaluation = false;
        private int units = 500;

        public GESystem(double mutationRate, double crossOverRate,
            UInt16 maxPoolSize,UInt16 maxGenerations, UInt16 maxTreeSize)
        {
            this.MutationRate = mutationRate;
            this.CrossOverRate = crossOverRate;
            this.MaxPoolSize = maxPoolSize;
            this.MaxGenerations = maxGenerations;
            this.MaxTreeSize = maxTreeSize;

            factory = new GEFactory();
            geGrammar = new Dictionary<string, List<LinkedList<string>>>();

            StrategyManager.StrategyCollection = new Collection<Strategy>();
            StrategyManager.ResultsStack = new Stack<ExpressionResult>();

            PortfolioManager.OpenPositions = new Collection<Position>();
        }

        private List<string[]> parseCSV(string path)
        {
            List<string[]> parsedData = new List<string[]>();

            try
            {
                using (StreamReader readFile = new StreamReader(path))
                {
                    string line;
                    string[] row;

                    while ((line = readFile.ReadLine()) != null)
                    {
                        row = line.Split(',');
                        parsedData.Add(row);
                    }
                }
            }
            catch (Exception e)
            {
                Console.WriteLine(e.Message);
            }

            return parsedData;
        }

        public void Initiate()
        {
            //Read Strategy Grammar
            using (StreamReader reader = new StreamReader("teststrat.json"))
            {
                string readString = reader.ReadToEnd();
                dynamic array = JsonConvert.DeserializeObject(readString);
                foreach (JProperty item in array)
                {
                    List<LinkedList<string>> optionsList = new List<LinkedList<string>>();
                    foreach (var options in item.Value)
                    {
                        LinkedList<string> operatorList = new LinkedList<string>();
                        foreach (var op in options)
                        {
                            operatorList.AddLast(op.ToString());
                        }
                        optionsList.Add(operatorList);
                    }
                    geGrammar.Add(item.Name, optionsList);
                }
            }

            Random rnd = new Random();

            //Generate Individual strategies
            for (int strategyNum = 0; strategyNum < 2000; strategyNum++)
            {
                PortfolioManager.ResetPortfolio();

                Console.WriteLine("");
                Strategy strategy = new Strategy
                {
                    OperatorList = new Collection<Operator>(),
                    TradeCount = 0
                };

                GenerateOperators("SIGNAL", rnd,strategy);
                StrategyManager.PrintSelectedStrategy(strategy);

                //Evaluate Strategy
                Console.Write("BackTesting Strategy");
                int i;
                string curDir = Directory.GetCurrentDirectory();
                string fileName = curDir + @"\msft.csv";
                List<string[]> parsedData = parseCSV(fileName);
                int nCount = parsedData.Count;
                double[] closingPricesArr = new double[nCount - 1];
                for (i = 200; i < nCount - 1; i++)
                {
                    if (i % 100 == 0)
                        Console.Write(".");

                    bool evaluationResult = EvaluateStrategyAtDelta(strategy,i);
                    DateTime currentDateTime = DateTime.Parse(parsedData[i + 1][0]);
                    float currentPrice = float.Parse(parsedData[i + 1][6]);

                    //Open a new LONG Position
                    if (evaluationResult && !prevEvaluation &&
                        !PortfolioManager.OpenPositions.Any())
                    {
                        //Console.Write(parsedData[i + 1][0]);
                        //Console.WriteLine("     BUY {0} Unit(s) of {1} at {2}", units,"MSFT",currentPrice);

                        Position position = new Position
                        {
                            Ticker = "MSFT",
                            PutPrice = currentPrice,
                            PutTimestamp = currentDateTime,
                            Units = units
                        };
                        PortfolioManager.OpenPositions.Add(position);
                        PortfolioManager.Capital -= (units * currentPrice);
                        strategy.TradeCount++;
                    }
                    //CLOSE position after expiry
                    else if (PortfolioManager.OpenPositions.Any())
                    {
                        TimeSpan elapsedTimeSpan = currentDateTime -
                                                   PortfolioManager.OpenPositions[0].PutTimestamp;
                        if (elapsedTimeSpan.Days >= 7)
                        {
                            //Console.Write(parsedData[i + 1][0]);
                            //Console.WriteLine("     SELL {0} Unit(s) of {1} at {2}", units,"MSFT", currentPrice);

                            PortfolioManager.Capital += (units * currentPrice);
                            PortfolioManager.OpenPositions.Clear();
                        }
                    }
                    prevEvaluation = evaluationResult;
                }

                StrategyManager.ResultsStack.Clear();
                StrategyManager.StrategyCollection.Add(strategy);
                StrategyManager.PrintStrategyPerformace(strategy);
            }
        }

        private bool EvaluateStrategyAtDelta(Strategy strategy,int delta)
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

        private void GenerateOperators(string grammarID, Random rnd,Strategy strategy)
        {
            LinkedList<string> signalGrammar = geGrammar[grammarID].
                ElementAt(rnd.Next(geGrammar[grammarID].Count));

            //Genrate selected signal functions
            for (int i = 0; i < signalGrammar.Count; i++)
            {
                //Is sub grammar exists
                if (geGrammar.ContainsKey(signalGrammar.ElementAt(i)))
                {
                    GenerateOperators(signalGrammar.ElementAt(i),rnd,strategy);
                }
                else
                {
                    try
                    {
                        int val = Int32.Parse(signalGrammar.ElementAt(i));
                        strategy.OperatorList.Add(new ValueTerminal(val));
                    }
                    catch (Exception)
                    {
                        switch (signalGrammar.ElementAt(i))
                        {
                            case "SMA": strategy.OperatorList.Add(new SMA());
                                break;
                            case "GTRE": strategy.OperatorList.Add(
                                new Comparator(ComparatorType.GRTE));
                                break;
                            case "LSTE": strategy.OperatorList.Add(
                                new Comparator(ComparatorType.LSTE));
                                break;
                            case "AND": strategy.OperatorList.Add(
                                new LogicalOperator(LogicalOperators.AND));
                                break;
                            case "OR": strategy.OperatorList.Add(
                                new LogicalOperator(LogicalOperators.OR));
                                break;
                        }
                    }
                }
            }            
        }
    }
}
