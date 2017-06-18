class AbstractPriceHandler(object):
    """
    PriceHandler is a base class providing an interface for
    all subsequent (inherited) data handlers (both live and historic).
    The goal of a (derived) PriceHandler object is to output a set of
    TickEvents or BarEvents for each financial instrument and place
    them into an event queue.
    This will replicate how a live strategy would function as current
    tick/bar data would be streamed via a brokerage. Thus a historic and live
    system will be treated identically by the rest of the QSTrader suite.
    """

    def UnsubscribeTicker(self,ticker):
        pass

    def GetLastTimestamp(self, ticker):
        pass

class AbstractOHLCVPriceHandler(AbstractPriceHandler):
    
    def IsBar(self):
        return True

    def StoreEvent(self, event):
        """
        Store price event for closing price and adjusted closing price
        """
        ticker = event.ticker

    def get_last_close(self,ticker):
        """
        Returns the most recent actual (unadjusted) closing price.
        """
        return 0           

