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
import combo
import optionchain
import optioncontract as contract

class Spread(combo.OptionCombo):
    contractA = None
    contractB = None

    def __init__(self, contractA, contractB):
        self.contractA = contractA
        self.contractB = contractB 

    @property
    def width(self):
        return abs(float(self.contractA.strike) - float(self.contractB.strike))

class SpreadConstructor():
    def __init__(self, optionChainManager):
        self.optionChainManager = optionChainManager

    def createStrikeSpread(self, underlyingSymbol, expirationDate, spreadtype, 
                              optiontype, strike0, strike1):
        contractA = self.optionChainManager.getContractData(underlyingSymbol, expirationDate, optiontype, strike0)
        contractB = self.optionChainManager.getContractData(underlyingSymbol, expirationDate, optiontype, strike1)

        return Spread(contractA, contractB)

    #Creates a spread with width W and a min market value of V at time D
    def createWidthValueSpread(self, underlyingSymbol, expirationDate, spreadtype,
                               optiontype, width, spreadvalue, curtimestamp):
        optionChain = self.optionChainManager.getOptionChain(underlyingSymbol, expirationDate)
        strikes = list(map(int,list(optionChain.strikes)))
        strikes.sort()
        curtimestamp = datetime.strptime(curtimestamp, '%d/%m/%Y')

        #TEMP Only consider strikes of multiples of 10
        for strike in strikes:
            if not (strike % 10) == 0:
                continue
            if strike + width > strikes[-1]:
                continue
            
            spread = self.createStrikeSpread(underlyingSymbol, expirationDate, spreadtype, optiontype, str(strike+width), str(strike))            
           
            if not curtimestamp in spread.contractA.marketData:
                continue
            if not curtimestamp in spread.contractB.marketData:
                continue

            dfA = spread.contractA.marketData[curtimestamp]
            dfB = spread.contractB.marketData[curtimestamp]

            if dfA.ask - dfB.ask >= spreadvalue:
                return spread        

    