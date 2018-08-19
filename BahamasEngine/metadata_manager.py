import csv

import settings
import option_chain
import option_contract

trading_dates = []
option_contracts = {}
option_chains = {}

def import_metadata():
    print("Loading metadata...")

    global trading_dates
    tdates_fpath = '{0}{1}//TRADINGDATES.txt'.format(settings.data_path, settings.ticker)
    trading_dates = open(tdates_fpath, 'r').read().splitlines()

    import_option_data()

    print("Loading metadata complete.")

def import_option_data():
    global option_contracts
    global option_chains

    manifest_fpath = '{0}{1}//MANIFEST.csv'.format(settings.data_path, 
    settings.ticker)
    with open(manifest_fpath, mode='r') as manifest_file:

        csv_reader = csv.reader(manifest_file, delimiter=',')
        for row in csv_reader:
            
            chain_id = row[0]
            contract_id = row[1]
            option_symbol = row[2]
            expiration_date = row[3]
            option_type = row[4]
            strike = float(row[5])
            start_date = row[6]

            if not chain_id in option_chains:
                chain = option_chain.OptionChain(chain_id, option_symbol, expiration_date, start_date)
                option_chains[chain_id] = chain

            if not contract_id in option_contracts:
                contract = option_contract.OptionContract(contract_id, chain_id, strike, option_type, start_date)
                option_contracts[contract_id] = contract

            target_chain = option_chains[chain_id]

            if option_type == 'C':
                target_chain.call_options.append(option_contracts[contract_id])
            elif option_type == 'P':
                target_chain.put_options.append(option_contracts[contract_id])