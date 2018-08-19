import sys
import math

import metadata_manager as md_manager

class Strategy(object):

    def __init__(self):
        pass

def get_dte_target_chain(option_chains, target_dte, data_manager):
    
    min_dte_diff = sys.maxsize
    target_chain = option_chains[0]

    for chain in option_chains:
        chain_dte = chain.get_dte(data_manager)
        dte_diff = abs(chain_dte - target_dte)

        if dte_diff < min_dte_diff and chain_dte >= target_dte:
            min_dte_diff = dte_diff
            target_chain = chain

    return target_chain             

def get_delta_target_contract(option_chain, tartget_delta, option_type, data_manager):

    target_contract = None
    min_delta_diff = sys.maxsize

    if option_type == 'C':
        raise Exception("Not Implemented for Option Type 'Call'")
    elif option_type == 'P':
        contract_count = len(option_chain.put_options)
        detla_values = [0.0] * contract_count

        for i in range(contract_count):
            contract_id = option_chain.put_options[i].contract_id

            if not md_manager.option_contracts[contract_id].is_tradable(data_manager):
                continue

            data_frame = data_manager.get_current_dataframe(contract_id)
            detla_values[i] = abs(data_frame.delta)

        for i in range(contract_count):
            delta_diff = abs(detla_values[i] - tartget_delta)
            if delta_diff < min_delta_diff:
                min_delta_diff = delta_diff
                target_contract = option_chain.put_options[i]

    return target_contract