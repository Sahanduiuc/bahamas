using System;
using System.Collections.Generic;

namespace BahamasEngine
{
    public class Structure
    {
        public List<SignalEvent> Positions { get; private set; }
        private InstrumentDataManager dataManager;

        public Structure(InstrumentDataManager dataManager, params SignalEvent[] contracts)
        {
            this.Positions = new List<SignalEvent>();
            this.dataManager = dataManager;

            for (int i = 0; i < contracts.Length; i++)
            {
                this.Positions.Add(contracts[i]);
            }
        }

        public void AddToStructure(SignalEvent contract)
        {
            Positions.Add(contract);
        }

        public double GetCost()
        {
            double value = 0.0;

            for (int i = 0; i < Positions.Count; i++)
            {
                double contractPrice = dataManager.GetCurrentPrice(Positions[i].Ticker);
                value += (contractPrice * Positions[i].Action * Positions[i].OrderUnits);
            }
            return value;
        }

        public double GetRegTRisk()
        {
            double maxRisk = double.MinValue;

            for (int i = 0; i < Positions.Count; i++)
            {
                OptionContract contract = dataManager.GetContractData(Positions[i].Ticker);

                double risk = GetRiskAtSlice(contract.Strike);
                if (risk > maxRisk)
                    maxRisk = risk;
            }
            return maxRisk;
        }

        public double GetRiskAtSlice(double priceSlice)
        {
            double riskVal = 0.0;

            for (int i = 0; i < Positions.Count; i++)
            {
                OptionContract contract = dataManager.GetContractData(Positions[i].Ticker);
                int units = Positions[i].OrderUnits;
                int action = Positions[i].Action;

                if (contract.Type == 'C')
                {
                    throw new NotImplementedException();
                }
                else if (contract.Type == 'P')
                {
                    double optVal = dataManager.GetCurrentPrice(contract.ID);
                    riskVal += dataManager.GetCurrentPrice(contract.ID) * action * units;
                    if (priceSlice < contract.Strike)
                        riskVal += (contract.Strike - priceSlice) * action * units * -1000;
                }
            }
            return riskVal;
        }
    }
}
