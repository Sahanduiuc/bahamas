import option_chain

class TradingEvent(object):

    def __init__(self):
        pass

class SignalEvent(TradingEvent):

    def __init__(self, option_id, action, units):
        self.option_id = option_id
        self.action = action
        self.units = units

class OrderEvent(TradingEvent):

    def __init__(self, option_id, action, units):
        self.option_id = option_id
        self.action = action
        self.units = units

class FillEvent(TradingEvent):

    def __init__(self, option_id, action, units, fill_price, commission):
        self.option_id = option_id
        self.action = action
        self.units = units
        self.fill_price = fill_price
        self.commission = commission

class TerminateEvent(TradingEvent):

    def __init__(self):
        pass                                

class OptionChainUpdateEvent(TradingEvent):

    def __init__(self):
        self.option_chains = []

          
        