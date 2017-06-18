from collections import deque

from price_handler.quandl_price_handler import QuandlPriceHandler

class Engine(object):
    
    def __init__(self,session_type = "backtest"):
        self.session_type = session_type
        self.eventsQueue = deque()

        self._ConfigureSession()

    def _ConfigureSession(self):
        self.price_handler = QuandlPriceHandler(
            "./data",self.eventsQueue,["SPY"]
        )

    def _execute_session(self):
        print("Running new Backtest") 
       

