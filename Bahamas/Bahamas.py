import optioncontract as contract
import datamanager as dm
import spread

dManager = dm.OptionChainDataManager("..\\data\\RUT\\","RUT")
tryGetContract = dManager.getContractDetails("RUT","19/02/2016","Call","900")

if not tryGetContract is None:
    print(tryGetContract)
