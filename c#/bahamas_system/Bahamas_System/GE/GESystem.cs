using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.Remoting.Messaging;
using System.Text;
using System.Threading.Tasks;
using bahamas_system.Bahamas_System.GE.Operators;
using bahamas_system.Bahamas_System.GE.Operators.Functions;
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
                    geGrammar.Add(item.Name,optionsList);
                }
            }

            //TODO Generate random strats


            Random rnd = new Random();
            for (int variationNum = 0; variationNum < MaxPoolSize; variationNum++)
            {
                //Create root node    
                Operator rootOperator = null;
                //Select rand function for root node
                int functionNum = rnd.Next(4);

                switch (functionNum)
                {
                    case 0: rootOperator = new SimpleAdd();
                        break;
                    case 1: rootOperator = new SimpleSub();
                        break;
                    case 2: rootOperator = new SimpleDiv(); 
                        break;
                    case 3: rootOperator = new SimpleMul(); 
                        break;
                    default: break;                            
                }

                //Create the sub-operators for the root operator
                factory.SetUpOperator(rootOperator);
             }
        }
    }
}
