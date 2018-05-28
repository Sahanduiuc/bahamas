from bokeh.io import curdoc
from bokeh.plotting import figure
from bokeh.layouts import column, row, WidgetBox
from datetime import datetime

import pandas as pd
import numpy as np

from scripts.risk_profile import risk_profile

df = pd.read_csv('D:\\bahamas_data\\CL\\FUT_Continuous.csv', low_memory=False)

p = figure(plot_width = 900, plot_height = 300, 
		title = 'CL1',
		x_axis_label = 'DateTime', y_axis_label = 'Value',
		x_axis_type='datetime')

dates = []
for date in df['Date']:
	dates.append(datetime.strptime(str(date), '%Y%m%d'))

p.line(dates, df['Settle'], line_width=2)

profile = risk_profile()

layout = row(p,profile)
		
curdoc().add_root(layout)