class Structure(object):

    def __init__(self, data_manager):
        self.positions = []
        self.data_manager = data_manager

    def add_to_structure(self, positions):
        self.positions.append(positions)

    def get_cost(self):
        value = 0.0

        for position in self.positions:
            option_price = self.data_manager.get_current_price(position.option_id)
            value += (option_price * position.action * position.units)

        return value

    def get_regt_risk(self):
        pass