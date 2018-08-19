import queue as queue

import portfolio
import order_sizer as os
import risk_manager as rm
import trading_event as trading_events

class PortfolioManager(object):
    
    def __init__(self, events_queue, data_manager, initial_balance):

        self.events_queue = events_queue
        self.data_manager = data_manager
        self.initial_balance = initial_balance
        self.current_balance = initial_balance

        self.portfolio = portfolio.Portfolio(events_queue, initial_balance, data_manager)

    def update_portfolio(self):

        self.portfolio.update_portfolio()

    def get_portfolio_value(self):

        return self.portfolio.equity

    def process_signal(self, s_event):

        m_order = os.MarketOrder(
            s_event.option_id,
            s_event.action,
            s_event.units,
            self.data_manager.get_current_price(s_event.option_id)
        )        

        m_order = os.size_order(m_order, self.portfolio)

        o_event = trading_events.OrderEvent(
            m_order.option_id,
            m_order.action,
            m_order.units
        )
        self.events_queue.put(o_event)

    def process_fill(self, f_event):

        self.portfolio.process_position(
            f_event.option_id,
            f_event.action,
            f_event.fill_price,
            f_event.units,
            f_event.commission
        )

    def liquid_portfolio(self):
        self.portfolio.liquidate_portfolio()


                            

        
