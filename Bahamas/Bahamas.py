import optionchain

cManager  = optionchain.OptionChainManager()
cManager.addNewInstrument("RUT")

print(cManager.getContractData("RUT","19/02/2016","Call","900"))