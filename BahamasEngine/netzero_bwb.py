import queue as queue

import settings
import structure as st
import statistics_manager as sm
import strategy_base as sb
import trading_event as trading_events

class NetZero(sb.Strategy):

    def __init__(self, events_queue, data_manager, p_manager, s_manager):
        self.events_queue = events_queue
        self.data_manager = data_manager
        self.p_manager = p_manager
        self.s_manager = s_manager
        self.last_traded_date = ""
        self.short_id = ""
        self.is_invested = False 

    def execute_strategy(self, update_event):

        current_date = self.data_manager.current_trading_date
        '''
        print("{0} {1} PnL {2}".format(            
            current_date,
            self.data_manager.current_timestamp_index,
            self.p_manager.get_portfolio_value() - 10000.0     
        ))
        '''

        self.s_manager.add_to_series(
            self.data_manager.current_timestamp_string,
            'NAV',
            self.p_manager.get_portfolio_value() - settings.account_balance
        )

        if self.is_invested:
            short_delta = self.data_manager.get_current_dataframe(self.short_id).delta * -100.0
            
            if (short_delta <= 20 or short_delta >= 60) and short_delta != 0.0:
                '''
                print("     {0} Closing Trade at Short Delta {1} with NAV {2}".format(
                    current_date,
                    short_delta,
                    self.p_manager.get_portfolio_value()
                ))
                '''
                self.p_manager.liquid_portfolio()
                self.is_invested = False
                self.last_traded_date = current_date
                t_event  = trading_events.TerminateEvent()
                self.events_queue.put(t_event)

        else:
            chain = sb.get_dte_target_chain(update_event.option_chains, 70, self.data_manager)

            target_options = sb.get_delta_target_contracts(
                chain,
                [0.6, 0.4, 0.2],
                'P',
                self.data_manager
            )
      
            order_60 = trading_events.SignalEvent(
                target_options[0].contract_id,
                1,
                1
            )
            order_40 = trading_events.SignalEvent(
                target_options[1].contract_id,
                -1,
                2
            )
            order_20 = trading_events.SignalEvent(
                target_options[2].contract_id,
                1,
                1
            )

            self.events_queue.put(order_60)
            self.events_queue.put(order_40)
            self.events_queue.put(order_20)

            o_structure = st.Structure(self.data_manager)
            o_structure.add_to_structure(order_60)
            o_structure.add_to_structure(order_40)
            o_structure.add_to_structure(order_20)
            
            cost = o_structure.get_cost()
            regt_risk = o_structure.get_regt_risk()
            '''  
            print("     {0} Starting new Trade on chain {1} with Cost {2} RegT {3}".format(
                current_date,
                chain.chain_id,
                cost,
                regt_risk
            ))
            '''
            self.s_manager.add_to_static(
                self.data_manager.current_timestamp_string, 
                "RegTRisk", 
                regt_risk
            )
            self.s_manager.add_to_static(
                self.data_manager.current_timestamp_string,
                "Cost",
                cost
            )

            self.is_invested = True
            self.short_id = order_40.option_id
            self.last_traded_date = current_date      
