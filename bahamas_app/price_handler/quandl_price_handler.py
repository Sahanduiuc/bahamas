import os
import numpy as np
import pandas as pd

from .base import AbstractOHLCVPriceHandler

class QuandlPriceHandler(AbstractOHLCVPriceHandler):
    """
    QuandlPriceHandler is designed to read CSV files of
    Qunadl Open-High-Low-Close-Volume (OHLCV) data
    for each requested financial instrument and stream those to
    the provided events queue as BarEvents.
    """
    def __init__(self, csvDir, eventsQueue,
                initTickers = None,
                startDate = None,
                endDate = None,
                calcAdjReturns = False):

        """
        Takes the CSV directory, the events queue and a possible
        list of initial ticker symbols then creates an (optional)
        list of ticker subscriptions and associated prices.
        """
        self.csvDir = csvDir
        self.eventsQueue = eventsQueue
        self.continueBacktest = True
        self.tickers = {}
        self.tickersData = {}
        if initTickers is not None:
            for ticker in initTickers:
                self.SubscribeTicker(ticker)                        
        self.startDate = startDate
        self.endDate = endDate
        self.calcAdjReturns = calcAdjReturns
        if self.calcAdjReturns:
            self.adjcloseReturns = []                


    def _ImportPriceData(self,ticker):
        """
        Opens the CSV files containing the equities ticks from
        the specified CSV data directory, converting them into
        them into a pandas DataFrame, stored in a dictionary.
        """
        tickerPath = os.path.join(self.csvDir, "%s.csv" % ticker)
        self.tickersData[ticker] = pd.io.parsers.read_csv(
            tickerPath, header=0, parse_dates=True,
            index_col=0, names=(
                "Date", "Open", "High", "Low",
                "Close", "Volume", "Adj Close"
            )
        )
        self.tickersData[ticker]["Ticker"] = ticker           

    def _MergeTickerData(self):
        pass

    def SubscribeTicker(self, ticker):
        if ticker not in self.tickers:
            try:
                self._ImportPriceData(ticker)
            except OSError:
                print("Failed to subscribe to ticker %s"
                    " as no data CSV found for pricing." % ticker)     
        else:
            print("Failed to subscribe to ticker %s"
                " as ticker is already subscribed." % ticker)


    def StreamNextEvent(self):
        """
        Place the next OHLCVEvent onto the event queue.
        """
        pass
