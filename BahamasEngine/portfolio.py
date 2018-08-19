import queue as queue
from numba import jit

import position
import trading_event as trading_events

class Portfolio(object):

    def __init__(self, events_queue, initial_balance, data_manager):
        
        self.events_queue = events_queue
        self.cash_balance = initial_balance
        self.initial_balance = initial_balance
        self.equity = initial_balance
        self.realised_pnl = 0.0
        self.unrealised_pnl = 0.0
        self.data_manager = data_manager

        self.invested_positions = {}

    def update_portfolio(self):

        self.unrealised_pnl = 0.0
        self.equity = self.initial_balance + self.realised_pnl

        for id, position in self.invested_positions.items():
            price = self.data_manager.get_current_price(id)
            position.update_market_value(price)
            self.unrealised_pnl += position.unrealised_pnl
            self.equity += (
                position.market_value - position.cost_basis + position.realised_pnl
            )

    def process_position(self, option_id, action, price, units, commission):

        if action == 0:
            return

        if action == 1:
            self.cash_balance -= ((price * units) + commission)
        elif action == -1:
            self.cash_balance += ((price * units) - commission)

        if option_id in self.invested_positions:
            self._update_position(option_id, action, units, price, commission)
        else:
            self._add_position(option_id, action, units, price, commission)    

    def liquidate_portfolio(self):

        for id, position in self.invested_positions.items():
            s_event = trading_events.SignalEvent(
                id,
                position.action,
                position.units
            )
            self.events_queue.put(s_event)    

    def _add_position(self, option_id, action, units, price, commission):
        
        self.invested_positions[option_id] = position.Poistion(
            option_id,
            action, 
            units,
            price,
            commission
            )
        self.update_portfolio()


    def _update_position(self, option_id, action, units, price, commission):
        
        self.invested_positions[option_id].update_position(action, units, price, commission)

        current_price = self.data_manager.get_current_price(option_id)

        self.invested_positions[option_id].update_market_value(current_price)

        if self.invested_positions[option_id].units == 0:
            self.realised_pnl += self.invested_positions[option_id].realised_pnl
            del self.invested_positions[option_id]

        self.update_portfolio()            