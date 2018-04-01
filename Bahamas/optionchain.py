# The MIT License (MIT)
#
# Copyright (c) 2018 Shamitha Ranasinghe
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

from datetime import datetime
import datamanager as dm
import optioncontract as contract
import marketdataframe as mdf

class OptionChain:
    strikes = set()
    expirationDate = None
    contracts = {}
    id = ""

    def __init__(self, underlyingSymbol, expirationDate):
        self.expirationDate = expirationDate
        self.underlyingSymbol = underlyingSymbol
        self.id = underlyingSymbol + "_" +expirationDate.strftime('%d/%m/%Y')

class OptionChainManager:
    __instrumentData = {}

    def __init__(self):
        pass

    def addNewInstrument(self, underlyingSymbol):
        dManager = dm.OptionDataImporter()
        data = dManager.importOptionData("C:\\Users\\shami\Desktop\\bahamas\\data\\RUT\\",underlyingSymbol)

        for eventDate, expDate, strike, type, mid in data:

            tContract = contract.OptionContract(expDate,
                                                strike,
                                                underlyingSymbol,
                                                type)
            bidaskDf = mdf.BidAskDataFrame(eventDate,mid, 0, mid, 0)

            chainId = underlyingSymbol + "_" + expDate.strftime('%d/%m/%Y')
            contractId = underlyingSymbol + "_" + expDate.strftime('%d/%m/%Y') + "_" + type + "_" + strike

            if not chainId in self.__instrumentData:
                oChain = OptionChain(underlyingSymbol, expDate)
                self.__instrumentData[chainId] = oChain

            if not strike in self.__instrumentData[chainId].strikes:
                self.__instrumentData[chainId].strikes.add(strike)

            if not contractId in self.__instrumentData[chainId].contracts:
                tContract = contract.OptionContract(expDate,
                                                    strike,
                                                    underlyingSymbol,
                                                    type)
                self.__instrumentData[chainId].contracts[contractId] = tContract

            self.__instrumentData[chainId].contracts[contractId].marketData[eventDate] = bidaskDf

    
    def getContractData(self, underlyingSymbol, expirationDate, type, strike):
        chainId = underlyingSymbol + "_" + expirationDate
        contractId = underlyingSymbol + "_" + expirationDate + "_" + type + "_" + strike

        if chainId in self.__instrumentData:
            if contractId in self.__instrumentData[chainId].contracts:
                return self.__instrumentData[chainId].contracts[contractId]
        print("Contract not found " + contractId)
        return None;

    def getOptionChain(self, underlyingSymbol, expirationDate):
        chainId = underlyingSymbol + "_" + expirationDate

        if chainId in self.__instrumentData:
            return self.__instrumentData[chainId]

        print("Option chain not found " + chainId)
        return None