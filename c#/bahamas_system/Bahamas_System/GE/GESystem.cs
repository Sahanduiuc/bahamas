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
        private Dictionary<string, List<LinkedList<string>>> geGrammarLimited;

        //TODO Portfolio Manager Implementation
        private bool prevEvaluation = false;
        private int units = 500;
        private int depth = 0;
        private int codonIndex;
        private int currentPoolSize = 0;
        private readonly int MAXCODONLENGTH = 100;

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
            geGrammarLimited = new Dictionary<string, List<LinkedList<string>>>();

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
            //Read Strategy Grammer (Limited set)
            using (StreamReader reader = new StreamReader("teststrat_limited.json"))
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
                    geGrammarLimited.Add(item.Name, optionsList);
                }
            }

            Random rnd = new Random();

            Console.WriteLine("Generating Initial Strategies");
            //Generate Individual strategies
            for (int strategyNum = 0; strategyNum < MaxPoolSize; strategyNum++)
            {
                if(strategyNum % 10 == 0)
                    Console.Write(".");

                //Console.WriteLine("");

                int[] codonPattern = Enumerable
                    .Repeat(0, MAXCODONLENGTH)
                    .Select(j => rnd.Next(0, 128))
                    .ToArray();

                //StrategyManager.PrintSelectedStrategy(strategy);
                StrategyManager.StrategyCollection.Add(
                GenerateCodonStrategy(codonPattern, rnd));
            }//End Strategy Creation

            for (int genNum = 0; genNum < MaxGenerations; genNum++)
            {

                Console.WriteLine("");
                Console.WriteLine("Generating Generation {0}",genNum);

                currentPoolSize = 0;
                Collection<Strategy> tempStrategies = new Collection<Strategy>();

                //Tournament Based Selection
                while (currentPoolSize < MaxPoolSize)
                {
                    if (currentPoolSize % 10 == 0)
                        Console.Write(".");

                    //Select 2 individuals using Tournament basis
                    Strategy strategy00 = SelectUsingFitness(
                        StrategyManager.StrategyCollection[rnd.Next(StrategyManager.StrategyCollection.Count)],
                        StrategyManager.StrategyCollection[rnd.Next(StrategyManager.StrategyCollection.Count)]);

                    Strategy strategy01 = SelectUsingFitness(
                        StrategyManager.StrategyCollection[rnd.Next(StrategyManager.StrategyCollection.Count)],
                        StrategyManager.StrategyCollection[rnd.Next(StrategyManager.StrategyCollection.Count)]);

                    int maxOperationPoint = strategy00.CodonLength < strategy01.CodonLength
                        ? strategy00.CodonLength
                        : strategy01.CodonLength;

                    int operationPoint = rnd.Next(1, maxOperationPoint);

                    //Perform Ripple CrossOver
                    var strategy00SubA = strategy00.CodonPattern.Take(operationPoint).ToArray();
                    var strategy00SubB = strategy00.CodonPattern.Skip(operationPoint).ToArray();

                    var strategy01SubA = strategy01.CodonPattern.Take(operationPoint).ToArray();
                    var strategy01SubB = strategy01.CodonPattern.Skip(operationPoint).ToArray();

                    int[] combinedCondonsA = strategy00SubA.Concat(strategy01SubB).ToArray();
                    int[] combinedCondonsB = strategy01SubA.Concat(strategy00SubB).ToArray();

                    Strategy genStrategy00 = GenerateCodonStrategy(combinedCondonsA, rnd);
                    Strategy genStrategy01 = GenerateCodonStrategy(combinedCondonsB, rnd);
                
                    tempStrategies.Add(genStrategy00);
                    currentPoolSize++;
                    tempStrategies.Add(genStrategy01);
                    currentPoolSize++;
                }

                StrategyManager.StrategyCollection.Clear();
                StrategyManager.StrategyCollection = tempStrategies;

                //Print Generation Statistics
            }
            Console.WriteLine("");
        }

        private Strategy GenerateCodonStrategy(int[] codonPattern, Random rnd)
        {
            Strategy strategy = new Strategy
            {
                OperatorList = new Collection<Operator>(),
                TradeCount = 0,
                CodonPattern = codonPattern,
                CodonLength = 0
            };

            depth = 0;
            codonIndex = 0;
            GenerateOperators("SIGNAL", rnd, strategy, codonPattern);
            strategy.CodonLength = codonIndex;

            return strategy;
        }

        private Strategy SelectUsingFitness(Strategy strategy00, Strategy strategy01)
        {
            //Evalaute fitness
            BackTestStrategy(ref strategy00);
            BackTestStrategy(ref strategy01);

            return strategy00.Returns > strategy01.Returns ? strategy00 : strategy01;
        }

        private void BackTestStrategy(ref Strategy strategy)
        {
            PortfolioManager.ResetPortfolio();

            //Evaluate Strategy
            //Console.WriteLine("BackTesting Strategy");

            //StrategyManager.PrintSelectedStrategy(strategy);

            int i;
            string curDir = Directory.GetCurrentDirectory();
            string fileName = curDir + @"\msft.csv";
            List<string[]> parsedData = parseCSV(fileName);
            int nCount = parsedData.Count;
            double[] closingPricesArr = new double[nCount - 1];
            for (i = 200; i < nCount - 1; i++)
            {
                //if (i % 100 == 0)
                //    Console.Write(".");

                bool evaluationResult = EvaluateStrategyAtDelta(strategy, i);
                DateTime currentDateTime = DateTime.Parse(parsedData[i + 1][0]);
                float currentPrice = float.Parse(parsedData[i + 1][6]);

                //Open a new LONG Position
                if (evaluationResult && !prevEvaluation &&
                    !PortfolioManager.OpenPositions.Any())
                {
                    //Console.Write(parsedData[i + 1][0]);
                    //Console.WriteLine("     BUY {0} Unit(s) of {1} at {2}", units, "MSFT", currentPrice);

                    Position position = new Position
                    {
                        Ticker = "MSFT",
                        PutPrice = currentPrice,
                        PutTimestamp = currentDateTime,
                        Units = units
                    };
                    PortfolioManager.OpenPositions.Add(position);
                    PortfolioManager.Capital -= (units*currentPrice);
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
                       // Console.WriteLine("     SELL {0} Unit(s) of {1} at {2} (EXPIRY)", units, "MSFT", currentPrice);

                        PortfolioManager.Capital += (units*currentPrice);
                        PortfolioManager.OpenPositions.Clear();
                    }
                    else
                    {
                        float priceDifference = currentPrice -
                                                PortfolioManager.OpenPositions[0].PutPrice;

                        if ((priceDifference*units) < -10)
                        {
                           // Console.Write(parsedData[i + 1][0]);
                            //Console.WriteLine("     SELL {0} Unit(s) of {1} at {2} (STOPLOSS)", units, "MSFT",currentPrice);

                            PortfolioManager.Capital += (units*currentPrice);
                            PortfolioManager.OpenPositions.Clear();
                        }
                        else if ((priceDifference*units) >= 100)
                        {
                            //Console.Write(parsedData[i + 1][0]);
                            //Console.WriteLine("     SELL {0} Unit(s) of {1} at {2} (TAKEPROFIT)", units, "MSFT",currentPrice);

                            PortfolioManager.Capital += (units*currentPrice);
                            PortfolioManager.OpenPositions.Clear();
                        }
                    }
                }
                prevEvaluation = evaluationResult;
            }

            StrategyManager.ResultsStack.Clear();
            //StrategyManager.PrintStrategyPerformace(strategy);

            StrategyManager.CalculateStrategyPerformance(ref strategy);
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

        private void GenerateOperators(string grammarID, Random rnd,Strategy strategy,
            int[] codonPattern)
        {
            LinkedList<string> signalGrammar;
            int grammarIndex;
            if (depth >= 2)
            {
                grammarIndex = codonPattern[codonIndex]%(geGrammarLimited[grammarID].Count);
                signalGrammar = geGrammarLimited[grammarID].
                    ElementAt(grammarIndex);
            }
            else
            {
                grammarIndex = codonPattern[codonIndex] % (geGrammar[grammarID].Count);
                signalGrammar = geGrammar[grammarID].
                    ElementAt(grammarIndex);
            }

            //Genrate selected signal functions
            for (int i = 0; i < signalGrammar.Count; i++)
            {
                codonIndex++;           
                //Is sub grammar exists
                if (geGrammar.ContainsKey(signalGrammar.ElementAt(i)))
                {
                    depth++;
                    GenerateOperators(signalGrammar.ElementAt(i),rnd,strategy,
                        codonPattern);
                }
                else
                {
                    try
                    {
                        int val = Int32.Parse(signalGrammar.ElementAt(i));
                        //Console.WriteLine(depth);
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
            depth--;
        }
    }
}
