using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Remoting.Messaging;
using System.Text;
using System.Threading.Tasks;
using bahamas_system.Bahamas_System.GE.Operators;
using bahamas_system.Bahamas_System.GE.Operators.Functions;

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

        public GESystem(double mutationRate, double crossOverRate,
            UInt16 maxPoolSize,UInt16 maxGenerations, UInt16 maxTreeSize)
        {
            this.MutationRate = mutationRate;
            this.CrossOverRate = crossOverRate;
            this.MaxPoolSize = maxPoolSize;
            this.MaxGenerations = maxGenerations;
            this.MaxTreeSize = maxTreeSize;

            factory = new GEFactory();
        }

        public void Initiate()
        {
            Random rnd = new Random();
            for (int iteration = 0; iteration < MaxPoolSize; iteration++)
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
             }
        }
    }
}
