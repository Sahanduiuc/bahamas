from bokeh.plotting import figure

def timeseries(xvals,yvals,title,xlabel,ylabel):

	plt = figure(plot_width = 800, plot_height = 200, title = title,
			x_axis_label = xlabel, y_axis_label = ylabel,
			x_axis_type="datetime")
	plt.line(xvals, yvals, line_width=2)
	
	return plt