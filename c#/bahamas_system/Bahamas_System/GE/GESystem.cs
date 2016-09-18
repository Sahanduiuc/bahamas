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
        private float buyingPower = 10000;
        private bool prevEvaluation = false;

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

            StrategyManager.OperatorList = new Collection<Operator>();
            StrategyManager.ResultsStack = new Stack<ExpressionResult>();
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

            //Random entry point on main grammar 
            Random rnd = new Random();
            GenerateOperators("SIGNAL", rnd);

            //Evaluate Strategy
            int i;
            string curDir = Directory.GetCurrentDirectory();
            string fileName = curDir + @"\msft.csv";
            List<string[]> parsedData = parseCSV(fileName);            
            int nCount = parsedData.Count;
            double[] closingPricesArr = new double[nCount - 1];
            for (i = 200; i < nCount - 1; i++)
            {
                bool evaluationResult = EvaluateStrategyAtDelta(i);

                if (evaluationResult && !prevEvaluation)
                {
                    Console.Write(parsedData[i + 1][0]);
                    Console.WriteLine("     BUY");
                    double currentPrice = Convert.ToDouble(parsedData[i + 1][6]);
                }

                prevEvaluation = evaluationResult;
            }


            Console.WriteLine("sds");
        }

        private bool EvaluateStrategyAtDelta(int delta)
        {
            StrategyManager.CurrentOperatorIndex = 0;

            while (StrategyManager.CurrentOperatorIndex < 
                StrategyManager.OperatorList.Count)
            {
                StrategyManager.OperatorList[StrategyManager.CurrentOperatorIndex].
                    Evaluate(delta);

                StrategyManager.CurrentOperatorIndex++;
            }

            return StrategyManager.ResultsStack.Pop().BinaryResult;
        }

        private void GenerateOperators(string grammarID, Random rnd)
        {
            LinkedList<string> signalGrammar = geGrammar[grammarID].
                ElementAt(rnd.Next(geGrammar[grammarID].Count));

            //Genrate selected signal functions
            for (int i = 0; i < signalGrammar.Count; i++)
            {
                //Is sub grammar exists
                if (geGrammar.ContainsKey(signalGrammar.ElementAt(i)))
                {
                    GenerateOperators(signalGrammar.ElementAt(i),rnd);
                }
                else
                {
                    try
                    {
                        int val = Int32.Parse(signalGrammar.ElementAt(i));
                        StrategyManager.OperatorList.Add(new ValueTerminal(val));
                    }
                    catch (Exception)
                    {
                        switch (signalGrammar.ElementAt(i))
                        {
                            case "SMA": StrategyManager.OperatorList.Add(new SMA());
                                break;
                            case "GTRE": StrategyManager.OperatorList.Add(
                                new Comparator(ComparatorType.GRTE));
                                break;
                            case "LSTE": StrategyManager.OperatorList.Add(
                                new Comparator(ComparatorType.LSTE));
                                break;
                            case "AND": StrategyManager.OperatorList.Add(
                                new LogicalOperator(LogicalOperators.AND));
                                break;
                            case "OR": StrategyManager.OperatorList.Add(
                                new LogicalOperator(LogicalOperators.OR));
                                break;
                        }
                    }
                }
            }            
        }
    }
}
