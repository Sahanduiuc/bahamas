import queue as queue

import settings
import data_manager as dm
import portfolio_manager as pm
import trading_event as trading_events

class Session(object):

    def __init__(self, eventsqueue, d_manager, p_manager, e_manager, strategy):
        self.eventsqueue = eventsqueue
        self.d_manager = d_manager
        self.p_manager = p_manager
        self.e_manager = e_manager
        self.strategy = strategy
        self.terminate = False

    def execute(self):
        print("Running new backtest session     Start Date {0} Start Time {1}".format(
            self.d_manager.current_trading_date,
            self.d_manager.current_timestamp_index + settings.time_step_size
        ))
   
        while not self.d_manager.eod():

            try:
                t_event = self.eventsqueue.get(False)
            except queue.Empty:
                if self.terminate == True:
                    break
                self.d_manager.stream_next_event()
            else:
                if t_event is not None:
                    if type(t_event) is trading_events.OptionChainUpdateEvent:
                        self.p_manager.update_portfolio()
                        self.strategy.execute_strategy(t_event)

                    elif type(t_event) is trading_events.SignalEvent:
                        self.p_manager.process_signal(t_event)

                    elif type(t_event) is trading_events.OrderEvent:
                        self.e_manager.execute_order(t_event)

                    elif type(t_event) is trading_events.FillEvent:
                        self.p_manager.process_fill(t_event)

                    elif type(t_event) is trading_events.TerminateEvent:
                        self.terminate = True

        print("Backtest session complete.")        