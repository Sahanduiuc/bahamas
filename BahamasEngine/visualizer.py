from bokeh.plotting import figure, output_file, show
from bokeh.models import DatetimeTickFormatter, LinearAxis, Range1d
from datetime import datetime
from operator import itemgetter

import settings

def plot(results):
    
    costs = []
    regtrisks = []
    dates = []
    nav_drawdowns = []
    nav_highs = []

    step_size = ((settings.time_end_index - settings.time_start_index) //
                settings.time_step_size) + 1

    for i in range(0, len(results), step_size):
        date = ''
        regt = 0.0
        cost = 0.0
        nav_drawdown = 0.0
        nav_max = 0.0
        for s in range(0, step_size):
            data = results[i + s].static_data['RegTRisk']
            date = data[0][0:8]
            regt += float(data[1])
            cost_data = results[i + s].static_data['Cost']
            cost += float(cost_data[1])
            navs = results[i + s].series_data['NAV']
            nav_max = max(navs,key=itemgetter(1))[1]
            nav_drawdown = min(navs,key=itemgetter(1))[1]

        regt = regt // step_size
        cost = cost // step_size
        dates.append(datetime.strptime(date, '%Y%m%d'))
        regtrisks.append(regt)
        costs.append(cost)
        nav_highs.append(nav_max)
        nav_drawdowns.append(nav_drawdown)

    plot_timeseries('PnL Stats', 1000, 300, dates, [
        (nav_highs,'PnL High'),
        (nav_drawdowns, 'PnL Max_Drawdown')
        ])

def plot_timeseries(title, width, height, x_data, series):
    plt = figure(
        title = title,
        plot_width = width,
        plot_height = height,
        x_axis_type = 'datetime'
    )

    colours_set = ['slateblue', 'tomato'] 

    for i in range(0, len(series)):
        plt.line(
            x_data,
            series[i][0],
            line_width = 2,
            color = colours_set[i % len(colours_set)],
            legend = series[i][1]
        )

    plt.xaxis.formatter=DatetimeTickFormatter(days=["%d-%m-%Y"])
    plt.xaxis.major_label_orientation = -0.5
    
    plt.yaxis.axis_label = "PnL ($)"

    show(plt)