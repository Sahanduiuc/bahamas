import os
import queue as queue
from multiprocessing import Process, Pool

import strategy_base
import netzero_bwb
import settings
import session
import metadata_manager as md_manager
import data_manager as dm
import portfolio_manager as pm
import execution_manager as em


def create_new_session(start_date, start_time_index):
    events_queue = queue.Queue()
    d_manager = dm.InstrumentDataManager(
        events_queue, 
        start_date, 
        start_time_index
    )
    p_manager = pm.PortfolioManager(events_queue, d_manager, settings.account_balance)
    e_manager = em.ExecutionManager(events_queue, d_manager)
    strategy = netzero_bwb.NetZero(events_queue, d_manager, p_manager)

    t_session = session.Session(events_queue, d_manager, p_manager, e_manager, strategy)
    t_session.execute()

def run():

    print(os.sched_getaffinity(0))

    md_manager.import_metadata()

    tasks = []
    for d_i in range(len(md_manager.trading_dates) - 1):
        for t_i in range(settings.time_start_index, settings.time_end_index, settings.time_step_size):
            tasks.append((d_i,t_i))

    p = Pool(10)
    #L = p.starmap(create_new_session, tasks)
    create_new_session(0,600)

run()