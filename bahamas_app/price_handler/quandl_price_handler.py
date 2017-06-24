import os
import numpy as np
import pandas as pd

from .base import AbstractOHLCVPriceHandler
from ..system_events import OHLCVEvent

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
        self.dataStream = self._MergeTickerData()
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
        """
        Concatenates all of the separate equities DataFrames
        into a single DataFrame that is time ordered, allowing tick
        data events to be added to the queue in a chronological fashion.
        Note that this is an idealised situation, utilised solely for
        backtesting. In live trading ticks may arrive "out of order".
        """
        df = pd.concat(self.tickersData.values()).sort_index()
        return df.iterrows()
       
    def _ConvertToEvent(self, row):
        openV = row["Open"]
        highV = row["High"]
        lowV = row["Low"]
        closeV  = row["Close"] 
        adjCloseV = row["Adj Close"]
        vv = row["Volume"] 

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
