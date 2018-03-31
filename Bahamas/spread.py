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

import combo
import datamanager
import optioncontract as contract

class Spread(combo.OptionCombo):
    def __init__(self, contractA, contractB):
        self.contractA = contractA
        self.contractB = contractB

    @property
    def width(self):
        return abs(float(self.contractA.strike) - float(self.contractB.strike))


class SpreadContructor():
    def __init__(self, dataManager):
        self.dataManager = dataManager

    def build_spread_for_credit(self, spreadtype,
                                optiontype, targetwidth, targetCredit):
        NotImplemented

    def build_spread_on_strikes(self, spreadtype, 
                                optiontype, strike0, strike1):
        NotImplemented


    