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
import marketdataframe as mdf
import glob
import csv
import optioncontract as contract

class OptionDataImporter:
    __instrumentData = {}

    def __init__(self):
        pass

    def getContractDetails(self, underlyingSymbol, expirationDate, type, strike):
        tContract = contract.OptionContract(datetime.strptime(expirationDate,'%d/%m/%Y'), 
                                            strike, underlyingSymbol, type)
        if tContract.id in self.__instrumentData:
            return self.__instrumentData[tContract.id]
        print("Contract not found " + tContract.id)
        return None

    def importOptionData(self, path, underlyingSymbol):
        self.underlyingSymbol = underlyingSymbol
        chainFiles = glob.glob(path + "*.csv")

        for file in chainFiles:
            print("Loading file "+file)           
            with open(file) as csvfile:
                readCSV = csv.reader(csvfile, delimiter=',')
                next(readCSV)
                for row in readCSV:
                    eventDate = datetime.strptime(row[0], '%d/%m/%Y')
                    expDate = datetime.strptime(row[1], '%d/%m/%Y')
                    strike = row[2]
                    type= row[3]
                    mid = float(row[4])
                    
                    yield eventDate, expDate, strike, type, mid

