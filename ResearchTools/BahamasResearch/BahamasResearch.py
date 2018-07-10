from bokeh.plotting import figure, output_file, show
from datetime import datetime
from bokeh.io import output_notebook
import pandas as pd
import numpy as np
import json

output_notebook()

def RenderBacktest():
    j = json.load(open('D:\\Backtest_Results\\131746912925578610_NZBWB.json'))
    seriesDates = []
    regTValues = []

    regTRaw = j['SeriesData']['RegTRisk']
    for tuple in regTRaw:
        seriesDates.append(datetime.strptime(tuple['Item1'], "%d/%m/%Y %H:%M:%S"))
        regTValues.append(tuple['Item2'])
    
    regTPlt = figure(plot_width = 950, plot_height = 375, title = 'NZBWB RegTRisk',
            x_axis_label = 'Date', y_axis_label = 'RegTRisk',
            x_axis_type="datetime")
    regTPlt.circle(seriesDates, regTValues, line_width=1)
    show(regTPlt)

RenderBacktest()