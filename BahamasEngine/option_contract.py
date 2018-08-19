from datetime import datetime

class OptionContract(object):

    def __init__(self, contract_id, chain_id, strike, option_type, write_date):
        self._contract_id = contract_id
        self._chain_id = chain_id
        self._strike = strike
        self._option_type = option_type
        self.write_date = datetime.strptime(write_date, '%Y%m%d')

    def is_tradable(self, data_manager):
        current_date = datetime.strptime(data_manager.current_trading_date, '%Y%m%d')
        days_diff = (self.write_date - current_date).days
        return days_diff <= 0

    @property
    def contract_id(self):
        return self._contract_id

    @property
    def chain_id(self):
        return self._chain_id

    @property
    def strike(self):
        return self._strike

    @property
    def option_type(self):
        return self._option_type          