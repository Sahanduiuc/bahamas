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
            }else if(optionType == 'P')
            {                
                foreach(OptionContract contract in optionChain.PutOptionContracts)
                {
                    double detla = Math.Abs(dataManager.GetCurrentOptionDataFrame(contract.ID).Delta);
                    double deltaDiff = Math.Abs(detla - targetDelta);
                    if (deltaDiff < minDeltaDiff)
                    {
                        minDeltaDiff = deltaDiff;
                        targetContract = contract;
                    }
                }
            }

            return targetContract;
        }
    }
}
