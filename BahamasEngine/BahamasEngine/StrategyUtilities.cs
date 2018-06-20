using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BahamasEngine
{
    public class StrategyUtilities
    {
        public StrategyUtilities() { }

        public OptionChainSnapshot GetDteTargetChain(IList<OptionChainSnapshot> optionChains,
            int targetDte)
        {
            int minDteDiff = Int32.MaxValue;
            OptionChainSnapshot targetChain = optionChains[0];

            foreach (OptionChainSnapshot chain in optionChains)
            {
                int dteDiff = Math.Abs(chain.OptionChain.Dte - targetDte);
                if (dteDiff < minDteDiff && chain.OptionChain.Dte >= targetDte)
                {
                    minDteDiff = dteDiff;
                    targetChain = chain;
                }
            }

            return targetChain;
        }

        public OptionContract GetDeltaTargetContract(OptionChainSnapshot optionChain,
            double targetDelta, char optionType, InstrumentDataManager dataManager)
        {
            OptionContract targetContract = null;
            double minDeltaDiff = Double.MaxValue;

            if (optionType == 'C')
            {
                throw new NotImplementedException();
            }
            else if (optionType == 'P')
            {
                int contractCount = optionChain.PutOptionContracts.Count;
                double[] deltaValues = new double[contractCount];
                List<Task> tasks = new List<Task>();

                for (int i = 0; i < contractCount; i++)
                {
                    int index = i;
                    Task t = Task.Run(async () => await CalculateDeltaValueAsync(index, deltaValues,
                        dataManager, optionChain.PutOptionContracts[index]));
                    tasks.Add(t);
                }

                Task.WaitAll(tasks.ToArray());

                for (int i = 0; i < contractCount; i++)
                {
                    double deltaDiff = Math.Abs(deltaValues[i] - targetDelta);
                    if (deltaDiff < minDeltaDiff)
                    {
                        minDeltaDiff = deltaDiff;
                        targetContract = optionChain.PutOptionContracts[i];
                    }
                }
            }

            return targetContract;
        }

        private async Task CalculateDeltaValueAsync(int index, double[] deltaValues,
            InstrumentDataManager dataManager, OptionContract contract)
        {
            string contractId = contract.ID;
            OptionDataFrame dataFrame = await dataManager.GetCurrentOptionDataFrameAsync(contractId);
            deltaValues[index] = Math.Abs(dataFrame.Delta);           
        }
    }
}
