import optionchain
import spread

cManager  = optionchain.OptionChainManager()
cManager.addNewInstrument("RUT")

sConstructor = spread.SpreadConstructor(cManager)
sConstructor.createWidthValueSpread("RUT","19/02/2016","Credit","Put",30,3,"04/01/2016")