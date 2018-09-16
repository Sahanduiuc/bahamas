import queue as queue

import settings
import strategy_base as sb

class ExprationStrategy(sb.Strategy):

    def __init__(self, events_queue, data_manager, p_manager, s_manager):
        self.events_queue = events_queue
        self.data_manager = data_manager
        self.p_manager = p_manager
        self.s_manager = s_manager

    def execute_strategy(self, update_event):

        current_date = self.data_manager.current_trading_date

        if current_date != '20180601':
            return

        chain = sb.get_dte_target_chain(update_event.option_chains,
            0,
            self.data_manager)

        target_options = sb.get_delta_target_contracts(
                chain,
                [0.5],
                'P',
                self.data_manager
            )

        print(chain.get_dte(self.data_manager))     

        return   

