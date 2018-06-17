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

                Task t1 = Task.Run(() => CalculateDeltaValues(0, contractCount / 2,
                    deltaValues, dataManager, optionChain.PutOptionContracts));
                Task t2 = Task.Run(() => CalculateDeltaValues(contractCount / 2, contractCount,
                    deltaValues, dataManager, optionChain.PutOptionContracts));

                Task.WaitAll(t1, t2);

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

        private void CalculateDeltaValues(int startIndex, int endIndex, double[] deltaValues,
            InstrumentDataManager dataManager, List<OptionContract> contracts)
        {
            for (int i = startIndex; i < endIndex; i++)
            {
                string contractId = contracts[i].ID;
                double delta = dataManager.GetCurrentOptionDataFrame(contractId).Delta;
                deltaValues[i] = Math.Abs(delta);
            }
        }
    }
}
