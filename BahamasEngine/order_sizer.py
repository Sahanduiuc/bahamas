class MarketOrder(object):

    def __init__(self, option_id, action, units, price):
        self.option_id = option_id
        self.action = action
        self.units = units
        self.price = price


def size_order(m_order, portfolio):

    #TODO Handle position sizing
    return m_order