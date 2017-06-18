from enum import Enum
from __future__ import print_function

EventType = Enum("EventType", "TICK BAR SIGNAL ORDER FILL SENTIMENT")

class Event(object):
    """
    Event is base class providing an interface for all subsequent
    (inherited) events, that will trigger further events in the
    trading infrastructure.
    """
    @property
    def typename(self):
        return self.type.name

class OHLCVEvent(Event):
    """
    Handles the event of receiving a new market
    open-high-low-close-volume bar, as would be generated
    via common data providers such as Qaundl.
    """            
    def __init__(self,ticker,time,period,
                openP,high, low, close, volume, adjClose = None):
        self.type = EventType.BAR
        self.ticker = ticker
        self.high= high
        self.low = low
        self.open = openP
        self.close = close
        self.volume = volume

