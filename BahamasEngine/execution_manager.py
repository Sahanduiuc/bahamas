import queue as queue

import settings
import trading_event as trading_events

class ExecutionManager(object):

    def __init__(self, events_queue, data_manager):
        self.events_queue = events_queue
        self.data_manager = data_manager

    def execute_order(self, o_event):

        f_event = trading_events.FillEvent(
            o_event.option_id,
            o_event.action,
            o_event.units,
            self.data_manager.get_current_price(o_event.option_id),
            settings.commission * o_event.units
        )

        self.events_queue.put(f_event)
