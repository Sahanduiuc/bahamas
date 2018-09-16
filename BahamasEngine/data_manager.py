import queue as queue 
import os.path
from datetime import timedelta

import settings
import trading_event as te
import metadata_manager as md_manager
import data_frames as df
import option_pricing_helper as p_helper

class InstrumentDataManager(object):

    def __init__(self, eventsqueue, start_date_index, start_time_index):
        self.eventsqueue = eventsqueue
        self.currentdateindex = start_date_index
        self.timestampindex = start_time_index - settings.time_step_size
        self.option_data_manager = OptionDataManager(self)

    def stream_next_event(self):
        self._get_next_timeindex()
        t_event = te.OptionChainUpdateEvent()

        for chain_id, chain in md_manager.option_chains.items():
            if not chain.is_tradable(self):
                continue

            dte = chain.get_dte(self)
            if dte >= 0:
                t_event.option_chains.append(chain)

        self.eventsqueue.put(t_event)

    def eod(self):
        if self.currentdateindex == len(md_manager.trading_dates) - 1:
            return True
        return False            

    def get_current_price(self, contract_id):
        data_frame = self.get_current_dataframe(contract_id)
        return calculate_mid_price(data_frame.bid, data_frame.ask)

    def get_current_dataframe(self, contract_id):
        return self.option_data_manager.get_current_dataframe(
            contract_id, 
            self.timestampindex,
            True
        )

    def get_underlying_price(self):
        return md_manager.underlying_data[self.current_trading_date][self.timestampindex - 571][1]

    def check_option_data(self, contract_id):
        date  = self.current_trading_date
        key = '{0}_{1}'.format(date, contract_id)

        f_path = '{0}{1}//OptionData//{2}//{3}.csv'.format(settings.data_path,
        settings.ticker, date, key)
        return os.path.isfile(f_path)

    def _get_next_timeindex(self):
        self.timestampindex += settings.time_step_size
        if self.timestampindex > settings.time_end_index:
            self.timestampindex = settings.time_start_index
            self.currentdateindex+=1

    @property
    def current_trading_date(self):
        return md_manager.trading_dates[self.currentdateindex]

    @property
    def current_timestamp_index(self):
        return self.timestampindex

    @property
    def current_timestamp_string(self):
        return "{0} {1}".format(
            self.current_trading_date,
            str(timedelta(minutes=self.timestampindex))
        )      


class OptionDataManager(object):

    def __init__(self, data_manager):
        
        self.data_manager = data_manager
        self.option_cache = {}

    def get_current_dataframe(self, contract_id, timeindex, calc_greeks):
        
        date = self.data_manager.current_trading_date
        key = '{0}_{1}'.format(date, contract_id)
        data = []

        if key not in self.option_cache:
            f_path = '{0}{1}//OptionData//{2}//{3}.csv'.format(settings.data_path,
            settings.ticker, date, key)
            data = open(f_path, 'r').read().splitlines()
            self.option_cache[key] = data
        else:
            data = self.option_cache[key]    

        target_row = data[timeindex - 571].split(',')

        bid = float(target_row[1])
        bid_size = int(target_row[2])
        ask = float(target_row[3]) 
        ask_size = int(target_row[4])
        underlying_price = float(target_row[5])

        mid_price = calculate_mid_price(bid, ask)  
        chain_id = md_manager.option_contracts[contract_id].chain_id
        dte = md_manager.option_chains[chain_id].get_dte(self.data_manager)
        option_type = md_manager.option_contracts[contract_id].option_type
        strike = md_manager.option_contracts[contract_id].strike

        delta = 0.0
        if calc_greeks:
            delta = calculate_option_delta(mid_price, underlying_price, strike, dte, option_type)

        data_frame = df.OptionDataFrame(
            contract_id, 
            date, 
            timeindex, 
            bid * settings.multiplier,
            bid_size, 
            ask * settings.multiplier, 
            ask_size, 
            delta,
            underlying_price)

        return data_frame

def calculate_option_delta(price, underlying_price, strike, dte, option_type):

    iv = p_helper.calculate_iv(underlying_price, strike, dte/365.0, price, option_type)

    if option_type == 'C':
        return p_helper.calculate_call_delta(underlying_price, strike, iv, dte/365.0)
    else:
        return p_helper.calculate_put_delta(underlying_price, strike, iv, dte/365.0)

def calculate_mid_price(bid, ask):
    return (bid + ask) / 2.0
