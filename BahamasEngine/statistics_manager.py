import numpy as np

import settings

class StatisticsManager(object):

    def __init__(self, session_id):
        self.session_id = session_id
        self.series_data = {}
        self.static_data = {}

    def add_to_series(self, timestamp, key, value):
        if key not in self.series_data:
            self.series_data[key] = []

        self.series_data[key].append((timestamp, value))

    def add_to_static(self, timestamp, key, value):
        self.static_data[key] = (timestamp, value)