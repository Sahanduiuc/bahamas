from bokeh.plotting import figure, output_file, show
from datetime import datetime
from bokeh.io import output_notebook
import pandas as pd
import numpy as np
import json

from BahamasResearch import TimeSeries as ts

output_notebook()

def render_backtest():
    j = json.load(open('D:\\Backtest_Results\\131772621076234716_NZBWB_5Min.json'))
    seriesDates = []
    regTValues = []

    regTRaw = j['SeriesData']['RegTRisk']
    for tuple in regTRaw:
        seriesDates.append(datetime.strptime(tuple['Item1'], "%d/%m/%Y %H:%M:%S"))
        regTValues.append(tuple['Item2'])
    
    regTSeries = ts.TimeSeries('NZBWB RegTRisk', 950, 375, 'Date', 'RegTRisk', seriesDates, regTValues)
    regTSeries.render_plot()

def process_report():
    pass

render_backtest()