from bokeh.plotting import figure, output_file, show

class TimeSeries(object):
    
    def __init__(self, title, width, height, xLabel, yLabel, xVals, yVals):
        self.series_plot = figure(plot_width = width, plot_height = height, 
            title = title,
            x_axis_label = xLabel, y_axis_label = yLabel,
            x_axis_type="datetime")
        self.series_plot.line(xVals, yVals, line_width=1)

    def render_plot(self):
        show(self.series_plot)