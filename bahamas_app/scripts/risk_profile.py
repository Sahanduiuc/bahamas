from bokeh.plotting import figure

def risk_profile():
	plt = figure(plot_width = 700, plot_height = 700, 
		title = 'Risk Profile',
		x_axis_label = 'Underlying', y_axis_label = 'PnL')
	
	return plt
	