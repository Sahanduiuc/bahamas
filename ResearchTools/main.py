from bokeh.io import curdoc
from bokeh.plotting import figure
from bokeh.layouts import column, row, WidgetBox
from bokeh.models import (CategoricalColorMapper, HoverTool, 
						  ColumnDataSource, Panel, 
						  FuncTickFormatter, SingleIntervalTicker, LinearAxis)
from bokeh.driving import count
from datetime import datetime

from threading import Timer,Thread,Event
import pandas as pd
import numpy as np
import pdfkit

from scripts.risk_profile import risk_profile
from scripts.timeseries import timeseries

df = pd.read_csv('D:\\bahamas_data\\CL\\FUT_Continuous.csv', low_memory=False)

dates = []
for date in df['Date']:
	dates.append(datetime.strptime(str(date), '%Y%m%d'))

p = timeseries(dates,df['Settle'],'CL','Date','Close',1000,300)

layout = row(p)
		
curdoc().add_root(layout)
#pdfkit.from_url('http://localhost:5006/bahamas_app', 'out.pdf')