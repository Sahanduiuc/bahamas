from numpy import sign

class Poistion(object):

    def __init__(self, option_id, action, units, purchase_price,
                commission):
        self.option_id = option_id
        self.action = action
        self.units = units
        self.purchase_price = purchase_price
        self.commission = commission

        self.realised_pnl = 0.0
        self.unrealised_pnl = 0.0

        self.units_bought = 0
        self.units_sold = 0
        self.avg_buy_value = 0.0
        self.avg_sell_value = 0.0
        self.total_buy_value = 0.0
        self.total_sell_value = 0.0
        self.net_commission = commission

        self._calculate_position_value()
        self.update_market_value(purchase_price)

    def _calculate_position_value(self):

        if self.action == 1:
            self.units_bought = self.units
            self.avg_buy_value = self.purchase_price
            self.total_buy_value = self.units_bought * self.purchase_price
            self.avg_value = ((self.purchase_price * self.units) + self.net_commission) // self.units
            self.cost_basis = self.units * self.avg_value
        elif self.action == -1:            
            self.units_sold = self.units
            self.avg_sell_value = self.purchase_price
            self.total_sell_value = self.units_sold * self.purchase_price
            self.avg_value = ((self.purchase_price * self.units) - self.net_commission) / self.units
            self.cost_basis = (self.units * self.avg_value) * -1.0
            
        self.net_units = self.units_bought - self.units_sold
        self.net_value = self.total_sell_value - self.total_buy_value
        self.net_value_after_commission = self.net_value - self.net_commission

    def update_market_value(self, price):
        
        self.mid_value = price
        self.market_value = self.units * self.mid_value * sign(self.net_units)
        self.unrealised_pnl = self.market_value - self.cost_basis
        self.realised_pnl = self.market_value + self.net_value_after_commission

    def update_position(self, action, units, price, commission):

        self.net_commission += commission

        if action == 1:
            self.avg_buy_value = (
                (self.avg_buy_value * self.units_bought) + (price * units)
                ) // (units + self.units_bought)
            self.avg_value = (
                (self.avg_value * self.units_bought) + (price * units) + commission
                ) // (units + self.units_bought)
            self.units_bought += units
            self.total_buy_value = self.units_bought * self.avg_buy_value

        elif action == -1:
            self.avg_sell_value = (
                (self.avg_sell_value * self.units_sold) + (price * units)
                ) // (units + self.units_sold)
            self.avg_value = (
                (self.avg_value * self.units_sold) + (price * units) - commission
                ) // (units + self.units_sold)
            self.units_sold += units
            self.total_sell_value = self.units_sold * self.avg_sell_value

        self.net_units = self.units_bought - self.units_sold
        self.units = self.net_units
        self.net_value = self.total_sell_value - self.total_buy_value
        self.net_value_after_commission = self.net_value - self.net_commission
        self.cost_basis = self.units * self.avg_value