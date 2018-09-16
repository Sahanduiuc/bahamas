import metadata_manager as md_manager

class Structure(object):

    def __init__(self, data_manager):
        self.positions = []
        self.data_manager = data_manager

    def add_to_structure(self, positions):
        self.positions.append(positions)

    def get_cost(self):
        value = 0.0

        for position in self.positions:
            option_price = self.data_manager.get_current_price(position.option_id)
            value += (option_price * position.action * position.units)

        return value

    def get_regt_risk(self):
        max_risk = -1

        for position in self.positions:
            contract = md_manager.option_contracts[position.option_id]

            risk = self.get_risk_at_slice(contract.strike)
            if risk > max_risk:
                max_risk = risk
        return max_risk        

    def get_risk_at_slice(self, price_slice):
        risk_val = 0.0

        for position in self.positions:            
            contract_id = position.option_id
            action = position.action
            units = position.units

            contract = md_manager.option_contracts[contract_id]

            if  contract.option_type == 'C':
                raise Exception("Call Type not implemented")
            elif contract.option_type == 'P':
                option_val = self.data_manager.get_current_price(contract_id)
                risk_val += option_val * action * units

                if price_slice < contract.strike:
                    risk_val += (contract.strike - price_slice) * action * units * -100              

        return risk_val        