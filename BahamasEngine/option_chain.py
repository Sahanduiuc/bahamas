from datetime import datetime

class OptionChain(object):

    def __init__(self, chain_id, option_symbol, expiration_date, start_date):
        self._chain_id = chain_id
        self._option_symbol = option_symbol
        self._expiration_date = datetime.strptime(expiration_date, '%Y%m%d')
        self._call_options = []
        self._put_options = []
        self.start_date = datetime.strptime(start_date, '%Y%m%d')

    def is_tradable(self, data_manager):
        current_date = datetime.strptime(data_manager.current_trading_date, '%Y%m%d')
        days_diff = (self.start_date - current_date).days
        return days_diff <= 0

    def get_dte(self, datamanager):
        current_date = datetime.strptime(datamanager.current_trading_date, '%Y%m%d')
        return (self._expiration_date - current_date).days

    @property
    def chain_id(self):
        return self._chain_id

    @property
    def option_symbol(self):
        return self._option_symbol

    @property
    def expiration_date(self):
        return self._expiration_date

    @property
    def call_options(self):
        return self._call_options

    @property
    def put_options(self):
        return self._put_options        