class OptionDataFrame(object):

    def __init__(self, option_id, event_date, event_timeindex, bid, bid_size,
                    ask, ask_size, delta, underlying_price):
        self._option_id = option_id
        self._event_date = event_date
        self._event_timeindex = event_timeindex
        self._bid = bid
        self._bid_size = bid_size
        self._ask = ask
        self._ask_size = ask_size
        self._delta = delta
        self._underlying_price = underlying_price

    @property
    def bid(self):
        return self._bid

    @property
    def ask(self):
        return self._ask

    @property
    def delta(self):
        return self._delta                            