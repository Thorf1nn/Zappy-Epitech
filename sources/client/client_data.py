#!/usr/bin/env python3
import sys


class ClientData:
    def __init__(self, name, client_num, x, y, sock):
        self.name = name
        self.client_num = client_num
        self.x = x
        self.y = y
        self.sock = sock
        self.player = False

        print("-->TEAM-NAME", self.name)
        print("<--CLIENT-NUM", self.client_num)
        print("<--X Y", self.x, self.y)

    ### Actions:
    def set_player(self, player):
        self.player = player

    def wait_message(self):
        msg = self.sock.receive_message()
        msg2 = msg.strip()
        mots = msg2.split()
        if "dead" in msg2:
            sys.exit(0)
        if msg2 == "ko":
            return msg2
        print("WORDS: " + msg2)
        if mots[0] != "Current":
            ret = self.my_broadcast(msg2)
            if ret == "fine":
                msg = self.sock.receive_message()
        return msg

    # Move
    def move(self, action):
        msg = action + "\n"
        self.sock.send_message(msg)
        move = self.sock.receive_message()
        move2 = move.replace("\n", "")
        if move2 != "ok":
            ret = self.my_broadcast(move2)
            if ret == "fine":
                move = self.sock.receive_message()
        return move

    def look(self):
        msg = "Look\n"
        self.sock.send_message(msg)
        map_game = self.sock.receive_message()
        try:
            if map_game[0] != "[":
                ret = self.my_broadcast(map_game)
                if ret == "fine":
                    map_game = self.sock.receive_message()
        except ConnectionError:
            print("")
        return map_game

    def inventory(self):
        msg = "Inventory\n"
        self.sock.send_message(msg)
        inv = self.sock.receive_message()
        if inv[0] != "[":
            ret = self.my_broadcast(inv)
            if ret == "fine":
                inv = self.sock.receive_message()
        return inv

    def broadcast_send(self, msg):
        msg = "Broadcast " + msg + "\n"
        self.sock.send_message(msg)
        msg = self.sock.receive_message()

    def nb_slots_unused(self):
        msg = "Connect_nbr\n"
        self.sock.send_message(msg)
        self.sock.receive_message()

    def fork(self):
        msg = "Fork\n"
        self.sock.send_message(msg)
        msg = self.sock.receive_message()
        msg = msg.replace("\n", "")
        if msg != "ok":
            ret = self.my_broadcast(msg)
            if ret == "fine":
                msg = self.sock.receive_message()

    def eject(self):
        msg = "Eject\n"
        self.sock.send_message(msg)
        msg = self.sock.receive_message()
        msg = msg.replace("\n", "")
        if msg != "ok" and msg != "ko":
            ret = self.my_broadcast(msg)
            if ret == "fine":
                msg = self.sock.receive_message()

    def take_object(self, object):
        msg = "Take " + object + "\n"
        self.sock.send_message(msg)
        res = self.sock.receive_message()
        res = res.replace("\n", "")
        if res != "ok" and res != "ko":
            ret = self.my_broadcast(res)
            if ret == "fine":
                res = self.sock.receive_message()

    def set_object(self, object):
        msg = "Set " + object + "\n"
        self.sock.send_message(msg)
        res = self.sock.receive_message()
        res2 = res.replace("\n", "")
        if res2 != "ok" and res2 != "ko":
            ret = self.my_broadcast(res2)
            if ret == "fine":
                res = self.sock.receive_message()
        return res

    def start_incantation(self):
        msg = "Incantation\n"
        self.sock.send_message(msg)
        res = self.sock.receive_message()
        print(res)
        res2 = res.strip()
        if res2 == "ko":
            return res2
        if res2 != "Elevation underway":
            ret = self.my_broadcast(res2)
            if ret == "fine":
                res = self.sock.receive_message()
        print("============== ELEVATION LEVEL: " + res)
        return res

    def dead(self):
        self.sock.receive_message()

    # Broadcast
    def wait_message_broadcast(self):
        msg = self.sock.receive_message()
        msg2 = msg.replace("\n", "")
        msg2 = msg2.split(",")[-1].strip()
        if ", " in msg2:
            split_message = msg.split(", ")
            msg = split_message[1]
        if msg2 == "Elevation underway":
            self.player.set_lvl(self.player.get_lvl() + 1)
        return msg2

    def broadcast_elevation_2players(self):
        print("=== I'm Freeze")
        while 1:
            msg = self.wait_message_broadcast()
            if msg == "dead":
                print("Player dead")
                sys.exit(0)
            if msg == "Play":
                break
        return "OK"

    def broadcast_elevation_4players(self):
        print("=== I'm Freeze")
        while 1:
            msg = self.wait_message_broadcast()
            if msg == "dead":
                print("Player dead")
                sys.exit(0)
            if msg == "Play4":
                break
        return "OK"

    def broadcast_elevation_6players(self):
        print("=== I'm Freeze")
        while 1:
            self.broadcast_send("Food Check")
            msg = self.wait_message_broadcast()
            if msg == "dead":
                print("Player dead")
                sys.exit(0)
            if self.player.get_food() <= 5:
                print("=== unFreeze je doit manger")
                break
            if msg == "Play6":
                break
            self.broadcast_send("Food Check")
        return "OK"

    def my_broadcast(self, msg):
        msg = msg.replace("\n", "")
        if ", " in msg:
            split_message = msg.split(", ")
            msg = split_message[1]

        if msg == "Freeze2" and self.player.get_lvl() == 2:
            return self.broadcast_elevation_2players()
        if msg == "Freeze4" and self.player.get_lvl() == 4:
            return self.broadcast_elevation_4players()
        if msg == "Freeze6" and self.player.get_lvl() == 6:
            return self.broadcast_elevation_6players()
        return "fine"

    ###

    def get_client_num(self):
        return self.client_num

    def get_world_size(self):
        return (self.x, self.y)
