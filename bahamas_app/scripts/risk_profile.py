from bokeh.plotting import figure

def risk_profile():
	plt = figure(plot_width = 600, plot_height = 600, 
		title = 'Risk Profile',
		x_axis_label = 'Underlying', y_axis_label = 'PnL')
	
	return plt
	