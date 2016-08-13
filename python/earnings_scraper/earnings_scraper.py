import re
import sys
import csv
import json
import click
import logging
import requests

from bs4 import BeautifulSoup
from yahoo_finance import Share
from datetime import datetime, timedelta


def get_sec_filing_urls(ticker):
    """ Returns a list of 8-K URLs for the given security.

    """
    filings = []
    params = {
        'action'    : 'getcompany',
        'CIK'       : ticker,
        'type'      : '8-K',
        'count'     : 100,
        'start'     : 0
    }

    while True:
        r = requests.get('https://www.sec.gov/cgi-bin/browse-edgar', 
                         params=params)
        soup = BeautifulSoup(r.text, 'html.parser')
        records = soup.find_all(text=re.compile('8-K'))

        # Pull out the 'Documents' URL for each record we found. 
        
        # <tr><td>Current report...</td><td><a href="...">Documents</a></td></tr>
        # ^   ^   ^                                  ^
        # |   |   |                                  |
        # |   |   record                             |
        # |   record.parent                          |
        # record.parent.parent                       |
        #                                            record.parent.parent.a['href']

        # Annoyingly they only use relative links, so we need to add 
        #the root domain back in.
        filings += ['https://www.sec.gov' + record.parent.parent.a['href'] 
                        for record in records]

        # Handle pagination
        if 'Next {}'.format(params['count']) in r.text:
            params['start'] = params['start'] + params['count']
            logging.debug("Fetching next page")
        else:
            break

    # SEC won't allow you to sort by date, so order them from oldest to
    # newest.
    filings.reverse()
    
    return filings


def get_filing_timestamp(url):
    """ Returns a string of the form yyyy-mm-dd HH:MM:SS containing the
        exact time the filing was submitted.

    """
    r = requests.get(url)
    soup = BeautifulSoup(r.text, 'html.parser')
    timestamp = soup.find(text=re.compile(r'\d{4}-\d\d-\d\d \d\d:\d\d:\d\d'))
    
    logging.debug("Timestamp for {}: {}".format(url, timestamp))

    return timestamp


def get_busystock_dates(ticker):
    """ Gets the earning dates from BusyStock.

    """
    dates = []

    r = requests.get('http://www.busystock.com/i.php', 
                     params={'s': ticker})
    soup = BeautifulSoup(r.text, 'html.parser')
    records = soup.find_all('td')

    # Pull out the 'Documents' URL for each record we found. 
    
    # <tr><td><a href="...">2016-05-12</a></td><td>NVDA...</td></tr>
    # ^   ^   ^                                  ^

    for row in soup.find_all('tr'):
        try:
            logging.debug(row.find_all('td')[0].a.text)
            dates.append(row.find_all('td')[0].a.text)
        except (IndexError, AttributeError):
            # Heading
            pass

    return dates


'''
def get_filings(timestamps, dates):
    """ Returns the timestamps which are a subset of the dates on
        BusyStock.

    """
    return map(lambda t, d: t if )
'''


def get_historical_prices(ticker, start_date, end_date):
    """ Gets the open and close prices for the given ticker over the
        range of dates.

    """
    # Need to get dates +/- 1 day
    start_date = datetime.strptime(start_date, '%Y-%m-%d')
    start_date_minus_1 = (start_date - timedelta(days=1)).strftime('%Y-%m-%d')
    end_date = datetime.strptime(end_date, '%Y-%m-%d')
    end_date_plus_1 = (end_date + timedelta(days=1)).strftime('%Y-%m-%d')

    security = Share(ticker)
    prices = security.get_historical(start_date_minus_1, end_date_plus_1)

    # Yahoo also returns from newest to oldest, so we must re-order
    prices.reverse()

    return prices


def dump_data(data, filename, out_format):
    """ Saves list of dictionaries to disk in either JSON or CSV format.

    """
    with open('{}.{}'.format(filename, out_format), 'w', newline='') as fh:
        if out_format == 'json':
            fh.write(json.dumps(data))
        elif out_format == 'csv':
            writer = csv.DictWriter(fh, data[0].keys())
            writer.writeheader()
            writer.writerows(data)


@click.command()
@click.option('-f', '--out-format', type=click.Choice(['json', 'csv']), 
              default='json', help="Format to save data")
@click.option('-v', '--verbose', default=False)
@click.argument('ticker')
def main(ticker, out_format, verbose):
    if verbose:
        logging.basicConfig(level=logging.DEBUG)

    logging.info("Getting filing dates for " + ticker)
    
    filings = get_sec_filing_urls(ticker)
    sec_timestamps = [get_filing_timestamp(filing) for filing in filings]
    busystock_dates = get_busystock_dates(ticker)
    #filing_dates = get_dates_subset(timestamps=sec_timestamps, 
    #                                dates=busystock_dates)
    
    prices = get_historical_prices(ticker, 
                                   sec_timestamps[0].split(' ')[0], 
                                   sec_timestamps[-1].split(' ')[0])

    dump_data([{'Timestamp': t} for t in sec_timestamps], 
              ticker + '_sec_timestamps', 
              out_format)
    dump_data([{'Date': d} for d in busystock_dates],
              ticker + '_busystock_dates',
              out_format)
    dump_data(prices, ticker + '_historical_data', out_format)


if __name__ == '__main__':
    main()