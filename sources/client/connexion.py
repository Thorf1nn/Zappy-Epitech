#!/bin/python3

import sys
from sources.client.client_data import ClientData
from sources.client.ai import ai_model

# check if the message is a welcome message and send the name to the server
def check_message_send(sock, name):
    data_encode = sock.receive_message()
    if data_encode == "WELCOME\n":
        sock.send_message(name + "\n")
        return True
    return False

# get the informations from the server
def get_infos(sock, name):
    infos = sock.receive_message()
    infos2 = sock.receive_message()
    lines = infos.strip().split("\n")
    lines2 = infos2.strip().split("\n")
    client_num = int(lines[0])
    x, y = map(int, lines2[0].split())

    # check if possible to connect
    # if (client_num < 1):
    #     print("Unable to connect a new client")
    #     sys.exit(84)

    client = ClientData(name, client_num, x, y, sock)

    ai_model(client)

def init_ai(sock, name):
    # check message
    if check_message_send(sock, name) == False:
        print("Error: problem with the server")
        sys.exit(84)
    # get infos
    get_infos(sock, name)
