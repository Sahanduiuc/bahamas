using System;
using System.Collections.Generic;

namespace BahamasEngine
{
    public class Structure
    {
        private List<OrderEvent> positions;
        private InstrumentDataManager dataManager;

        public Structure(InstrumentDataManager dataManager, params OrderEvent[] contracts)
        {
            this.positions = new List<OrderEvent>();
            this.dataManager = dataManager;

            for (int i = 0; i < contracts.Length; i++)
            {
                this.positions.Add(contracts[i]);
            }
        }

        public void AddToStructure(OrderEvent contract)
        {
            positions.Add(contract);
        }

        public double GetCost()
        {
            double value = 0.0;

            for (int i = 0; i < positions.Count; i++)
            {
                double contractPrice = dataManager.GetCurrentPrice(positions[i].Ticker);
                value += (contractPrice * positions[i].Action * positions[i].OrderUnits);
            }
            return value;
        }

        public double GetRegTRisk()
        {
            double maxRisk = double.MinValue;

            for (int i = 0; i < positions.Count; i++)
            {
                OptionContract contract = dataManager.GetContractData(positions[i].Ticker);

                double risk = GetRiskAtSlice(contract.Strike);
                if (risk > maxRisk)
                    maxRisk = risk;
            }
            return maxRisk;
        }

        public double GetRiskAtSlice(double priceSlice)
        {
            double riskVal = 0.0;

            for (int i = 0; i < positions.Count; i++)
            {
                OptionContract contract = dataManager.GetContractData(positions[i].Ticker);
                int units = positions[i].OrderUnits;
                int action = positions[i].Action;

                if (contract.Type == 'C')
                {
                    throw new NotImplementedException();
                }
                else if (contract.Type == 'P')
                {
                    riskVal += dataManager.GetCurrentPrice(contract.ID) * action * units;
                    if (priceSlice < contract.Strike)
                        riskVal += (contract.Strike - priceSlice) * action * units * -1000;
                }
            }
            return riskVal;
        }
    }
}
