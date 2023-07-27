#!/usr/bin/env python3

import sys
from sources.client.communication import Communication
from sources.client.parsing import Parsing
from sources.client.connexion import init_ai
# from sources.client.keras_model import initialize_model

def print_usage():
    print("USAGE: ./zappy_ai -p port -n name -h machine")
    print("       port     is the port number")
    print("       name     is the name of the team")
    print("       machine  is the name of the machine; localhost by default")

def main():
    if len(sys.argv) == 2 and sys.argv[1] == "-help":
        print_usage()
        return 0

    # init Parsing
    parser = Parsing()
    parser.error_handing()
    parser.run()

    # Get arguments
    port = parser.get_port()
    name = parser.get_name()
    machine = parser.get_machine()

    # Create Communication
    sock = Communication(port, machine)

    # Init Ai parameters with communication
    # initialize_model()

    init_ai(sock, name)

    # End of the main
    sock.close()

if __name__ == '__main__':
    main()