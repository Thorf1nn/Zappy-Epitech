#!/bin/python3

class Player:
    def __init__(self, client):
        self.client = client
        self.lvl = 1
        self.food = 10
        self.linemate = 0
        self.deraumere = 0
        self.sibur = 0
        self.mendiane = 0
        self.phiras = 0
        self.thystame = 0

    def set_lvl(self, lvl):
        self.lvl = lvl

    def set_food(self, food):
        self.food = food

    def set_linemate(self, linemate):
        self.linemate = linemate

    def set_deraumere(self, deraumere):
        self.deraumere = deraumere

    def set_sibur(self, sibur):
        self.sibur = sibur

    def set_mendiane(self, mendiane):
        self.mendiane = mendiane

    def set_phiras(self, phiras):
        self.phiras = phiras

    def set_thystame(self, thystame):
        self.thystame = thystame

    def elevation_lvl2(self):
        self.client.set_object("linemate")

        msg = self.client.start_incantation()
        msg = msg.replace("\n", "")
        if (msg != "ko"):
            self.client.wait_message()
            self.lvl += 1

    def elevation_lvl3(self):
        self.client.set_object("linemate")
        self.client.set_object("deraumere")
        self.client.set_object("sibur")

        msg = self.client.start_incantation()
        msg = msg.replace("\n", "")
        if (msg != "ko"):
            self.client.wait_message()
            self.lvl += 1

    def elevation_lvl4(self):
        self.client.set_object("linemate")
        self.client.set_object("linemate")
        self.client.set_object("sibur")
        self.client.set_object("phiras")
        self.client.set_object("phiras")

        msg = self.client.start_incantation()
        print(msg)
        msg = msg.replace("\n", "")
        if (msg != "ko"):
            self.client.wait_message()
            self.lvl += 1

    def elevation_lvl5(self):
        self.client.set_object("linemate")
        self.client.set_object("deraumere")
        self.client.set_object("sibur")
        self.client.set_object("sibur")
        self.client.set_object("phiras")

        msg = self.client.start_incantation()
        msg = msg.replace("\n", "")
        if (msg != "ko"):
            self.client.wait_message()
            self.lvl += 1

    def elevation_lvl6(self):
        self.client.set_object("linemate")
        self.client.set_object("deraumere")
        self.client.set_object("deraumere")
        self.client.set_object("sibur")
        self.client.set_object("mendiane")
        self.client.set_object("mendiane")
        self.client.set_object("mendiane")

        msg = self.client.start_incantation()
        msg = msg.replace("\n", "")
        if (msg != "ko"):
            self.client.wait_message()
            self.lvl += 1

    def elevation_lvl7(self):
        self.client.set_object("linemate")
        self.client.set_object("deraumere")
        self.client.set_object("deraumere")
        self.client.set_object("sibur")
        self.client.set_object("sibur")
        self.client.set_object("sibur")
        self.client.set_object("phiras")

        msg = self.client.start_incantation()
        msg = msg.replace("\n", "")
        if (msg != "ko"):
            self.client.wait_message()
            self.lvl += 1

    def elevation_lvl7(self):
        self.client.set_object("linemate")
        self.client.set_object("linemate")
        self.client.set_object("deraumere")
        self.client.set_object("deraumere")
        self.client.set_object("sibur")
        self.client.set_object("sibur")
        self.client.set_object("mendiane")
        self.client.set_object("mendiane")
        self.client.set_object("phiras")
        self.client.set_object("phiras")
        self.client.set_object("thystame")

        msg = self.client.start_incantation()
        msg = msg.replace("\n", "")
        if (msg != "ko"):
            self.client.wait_message()
            self.lvl += 1

    def get_lvl(self):
        return self.lvl

    def get_food(self):
        return self.food

    def get_linemate(self):
        return self.linemate

    def get_deraumere(self):
        return self.deraumere

    def get_sibur(self):
        return self.sibur

    def get_mendiane(self):
        return self.mendiane

    def get_phiras(self):
        return self.phiras

    def get_thystame(self):
        return self.thystame
