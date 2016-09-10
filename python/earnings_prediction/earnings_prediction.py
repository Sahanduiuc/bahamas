import csv
import click
import logging
import numpy as np

from collections import Counter
from datetime import datetime, timedelta


DATE_FORMAT = '%Y-%m-%d'


def parse_dates(dates_file, data_format):
    """ Parses a list of earnings dates from given file.

    """
    if data_format != 'csv':
        logging.critical("Only CSV files currently supported")
        exit()

    return [datetime.strptime(date[0], DATE_FORMAT) 
                for date in list(csv.reader(dates_file))[1:]]


def parse_prices(prices_file, data_format):
    """ Parses list of price points from CSV file.
    
    """
    if data_format != 'csv':
        logging.critical("Only CSV files currently supported")
        exit()

    reader = csv.DictReader(prices_file)
    prices = [row for row in reader]
    for price in prices:
        price.update(
            { 
                'Date': datetime.strptime(price['Date'], DATE_FORMAT),
                'Low': float(price['Low']),
                'High': float(price['High']),
                'Open': float(price['Open']),
                'Close': float(price['Close'])
            })

    return {price['Date']: price for price in prices}


def get_close_price_for_date(prices, date):
    """ Returns price data for a specific date.

    """
    return prices[date]['Close']


def compute_state_transitions(earnings_dates, prices):
    """ Computes the Markov chain for the given set of dates and prices.
    
    """
    states = []

    for earnings_date in earnings_dates:
        # Get earnings date +/- 1 day prices
        # FIXME: This breaks if earnings released on weekend!
        try:
            price_on_earnings_plus_1 = get_close_price_for_date(
                                            prices,
                                            earnings_date + timedelta(days=1))
            price_on_earnings_minus_1 = get_close_price_for_date(
                                            prices,
                                            earnings_date - timedelta(days=1))

            if price_on_earnings_plus_1 > price_on_earnings_minus_1:
                states.append(0)    # Long position
            else:
                states.append(1)    # Short position
        except KeyError:
            # Ignore out-of-range dates
            logging.warn("Skipping out-of-range date {}".format(earnings_date))

    return states


def compute_transition_matrix(states):
    """ Computes the transition probabilities for a given set of states.

    """
    transition_matrix = np.zeros((2, 2))
    for (x, y), c in Counter(zip(states, states[1:])).items():
        transition_matrix[x, y] = c

    row_sums = transition_matrix.sum(axis=1)

    # Normalise
    return transition_matrix / row_sums[:, np.newaxis]

@click.command()
@click.option('-f', '--data-format', type=click.Choice(['json', 'csv']), 
              default='json', help="Format to save data")
@click.option('-v', '--verbose', default=True)
@click.argument('dates_file', type=click.File(), required=True)
@click.argument('prices_file', type=click.File(), required=True)
@click.argument('ticker')
def main(data_format, dates_file, prices_file, ticker, verbose):
    if verbose:
        logging.basicConfig(level=logging.DEBUG)

        dates = parse_dates(dates_file, data_format)
        prices = parse_prices(prices_file, data_format)
        states = compute_state_transitions(dates, prices)
        transition_matrix = compute_transition_matrix(states)
        
        logging.debug(states)
        logging.debug(transition_matrix)

if __name__ == '__main__':
    main()