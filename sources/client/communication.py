#!/bin/python3

import socket

class Communication:
    # Init the socket
    def __init__(self, port, machine):
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.sock.connect((machine, port))
        self.buffer = ""

    # Receive message from the server
    def receive_message(self):
        while "\n" not in self.buffer:
            try:
                received_data = self.sock.recv(4096).decode()
                if len(received_data) == 0:
                    raise Exception("Server disconnected")
                self.buffer += received_data
            except ConnectionError:
                raise Exception("Server disconnected")
        end_index = self.buffer.index("\n")
        data = self.buffer[:end_index]
        self.buffer = self.buffer[end_index + 1:]
        return data + '\n'

    # Send message to the server
    def send_message(self, msg):
        try:
            self.sock.sendall(msg.encode())
            return True
        except Exception as e:
            print("Error occurred while sending message:", str(e))
            return False

    # Close the socket
    def close(self):
        self.sock.close()
