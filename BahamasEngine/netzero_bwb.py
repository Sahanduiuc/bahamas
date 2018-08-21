import queue as queue

import strategy_base as sb
import trading_event as trading_events

class NetZero(sb.Strategy):

    def __init__(self, events_queue, data_manager, p_manager):
        self.events_queue = events_queue
        self.data_manager = data_manager
        self.p_manager = p_manager
        self.last_traded_date = ""
        self.short_id = ""
        self.is_invested = False 

    def execute_strategy(self, update_event):

        current_date = self.data_manager.current_trading_date
    
        print("{0} {1} PnL {2}".format(            
            current_date,
            self.data_manager.current_timestamp_index,
            self.p_manager.get_portfolio_value() - 10000.0     
        ))

        if current_date == self.last_traded_date:
            return

        if self.is_invested:
            short_delta = self.data_manager.get_current_dataframe(self.short_id).delta * -100.0
            
            if (short_delta <= 20 or short_delta >= 60) and short_delta != 0.0:
                print("     {0} Closing Trade at Short Delta {1} with NAV {2}".format(
                    current_date,
                    short_delta,
                    self.p_manager.get_portfolio_value()
                ))
                self.p_manager.liquid_portfolio()
                self.is_invested = False
                self.last_traded_date = current_date
                t_event  = trading_events.TerminateEvent()
                self.events_queue.put(t_event)

        else:
            chain = sb.get_dte_target_chain(update_event.option_chains, 70, self.data_manager)
        
            print("     {0} Starting new Trade on chain {1}".format(
                current_date,
                chain.chain_id
            ))

            d_60_contract = sb.get_delta_target_contract(
                chain,
                0.6,
                'P',
                self.data_manager
            )
            d_40_contract = sb.get_delta_target_contract(
                chain,
                0.4,
                'P',
                self.data_manager
            )
            d_20_contract = sb.get_delta_target_contract(
                chain,
                0.2,
                'P',
                self.data_manager
            )
        
            order_60 = trading_events.SignalEvent(
                d_60_contract.contract_id,
                1,
                1
            )
            order_40 = trading_events.SignalEvent(
                d_40_contract.contract_id,
                -1,
                2
            )
            order_20 = trading_events.SignalEvent(
                d_20_contract.contract_id,
                1,
                1
            )

            self.events_queue.put(order_60)
            self.events_queue.put(order_40)
            self.events_queue.put(order_20)

            self.is_invested = True
            self.short_id = d_40_contract.contract_id
            self.last_traded_date = current_date      
