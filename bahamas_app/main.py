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

from scripts.risk_profile import risk_profile

df = pd.read_csv('D:\\bahamas_data\\CL\\FUT_Continuous.csv', low_memory=False)
p = figure(plot_width = 750, plot_height = 250, 
		title = 'CL1',
		x_axis_label = 'DateTime', y_axis_label = 'Value',
		x_axis_type='datetime')

dates = []
for date in df['Date']:
	dates.append(datetime.strptime(str(date), '%Y%m%d'))

pdDs = dict(x=[], y=[])
src = ColumnDataSource(pdDs)

@count()	
def update(t):
	#count = count + 1
	new_data = {
		'x' : dates[t:t+1],
		'y' : df['Settle'][t:t+1],
	}
	src.stream(new_data)

p.line(x='x', y='y', line_width=2, source=src)

profile = risk_profile()

layout = row(p,profile)
		
curdoc().add_root(layout)
curdoc().add_periodic_callback(update, 500)