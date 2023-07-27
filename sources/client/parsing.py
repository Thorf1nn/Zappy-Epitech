import argparse
import sys

class Parsing:
    def __init__(self):
        self.parser = argparse.ArgumentParser(prog='./zappy_ai', description='zappy_ai command-line arguments', add_help=False)
        self.port = 0
        self.name = 0
        self.machine = 0
        self.parser.add_argument('-p', dest='port', type=int, help='Port number')
        self.parser.add_argument('-n', dest='name', type=str, help='Name of the team')
        self.parser.add_argument('-h', dest='machine', type=str, default='localhost', help='Name of the machine')

    def parse_arguments(self):
        return self.parser.parse_args()

    def error_handing(self):
        args = self.parse_arguments()
        if args.port is None or args.name is None:
            print("Error: Invalid number of arguments")
            sys.exit(84)

    def run(self):
        args = self.parse_arguments()
        self.port = args.port
        self.name = args.name
        self.machine = args.machine

    def get_port(self):
        return self.port

    def get_name(self):
        return self.name

    def get_machine(self):
        return self.machine

    def set_things(self, port, name, machine):
        self.port = port
        self.name = name
        self.machine = machine
