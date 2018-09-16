import os
import queue as queue
import numpy as np
from multiprocessing import Process, Pool

import strategy_base
import netzero_bwb
import strat_expiration
import settings
import session
import metadata_manager as md_manager
import data_manager as dm
import portfolio_manager as pm
import execution_manager as em
import statistics_manager as sm
import visualizer as viz

def create_new_session(start_date, start_time_index):
    events_queue = queue.Queue()
    
    s_manager = sm.StatisticsManager(
        '{0}_{1}'.format(start_date, start_time_index)
    )
    d_manager = dm.InstrumentDataManager(
        events_queue, 
        start_date, 
        start_time_index
    )
    p_manager = pm.PortfolioManager(events_queue, d_manager, settings.account_balance)
    e_manager = em.ExecutionManager(events_queue, d_manager)
    strategy = strat_expiration.ExprationStrategy(events_queue, d_manager, p_manager, s_manager)

    t_session = session.Session(events_queue, d_manager, p_manager, e_manager, strategy)
    t_session.execute()

    return s_manager

def run():
    print(os.sched_getaffinity(0))

    md_manager.import_metadata()

    standard = True

    if not standard:
        tasks = []
        for d_i in range(len(md_manager.trading_dates) - 1):
            for t_i in range(
                settings.time_start_index, 
                settings.time_end_index + settings.time_step_size,
                settings.time_step_size):
                
                tasks.append((d_i,t_i))

        p = Pool(8)
        results = p.starmap(create_new_session, tasks)

        viz.plot(results)
    else:
        result = create_new_session(0, settings.time_start_index)

run()
