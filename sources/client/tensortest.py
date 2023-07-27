#!/usr/bin/env python3

import tensorflow as tf
import numpy as np
import sys
import re
import time

from sources.client.client_data import ClientData
from sources.client.parsing import Parsing
from sources.client.communication import Communication
from sources.client.connexion import check_message_send

# Define the game environment class
class GameEnvironment:
    def __init__(self, action_choose):
        # Initialize the game environment
        # Include necessary variables and methods to interact with the game server
        self.resources = {
            'food': 10,
            'linemate': 0,
            'deraumere': 0,
            'sibur': 0,
            'mendiane': 0,
            'phiras': 0,
            'thystame': 0
        }
        self.elevation = 1
        self.action = action_choose

    def get_state(self):
        # Return the current state of the game environment
        # Can include player's position, inventory, and other relevant information
        return np.array(list(self.resources.values()))

    def take_action(self, action):
        if action == "Forward\n":
            self.action.move(action)
            return
        if action == "Right\n":
            self.action.move(action)
            return
        if action == "Left\n":
            self.action.move(action)
            return
        if action == "Eject\n":
            self.action.eject()
            return
        if action == "Fork\n":
            self.action.fork()
            return
        if action == "Incantation\n":
            required_resources = self.get_required_resources(self.elevation)
            if self.has_enough_resources(required_resources):
                if self.action.start_incantation() != "ko":
                    # Perform the incantation and update the state
                    self.update_resources(required_resources)
                    self.elevation += 1
                self.client.wait_message()
            return

        split_string = action.split()
        action_do = split_string[0]
        object = split_string[1]

        if action_do == "Take":
            self.action.take_object(object)
            return
        if action_do == "Broadcast":
            self.action.broadcast_send(object)
            return
        if action_do == "Set":
            self.action.set_object(object)
            return

    def get_reward(self):
        if self.elevation == 2:
            return 100
        if self.elevation == 3:
            return 150
        if self.elevation == 4:
            return 200
        if self.elevation == 5:
            return 250
        if self.elevation == 6:
            return 300
        if self.elevation == 7:
            return 350
        if self.elevation == 8:
            return 500

        total_resources = sum(self.resources.values())
        reward = total_resources * 10  # Give 10 points for each collected resource

        return reward
    
    def is_done(self):
        if self.elevation == 8:
            return True
        if self.resources['food'] == 0:
            return True

    def get_required_resources(self, elevation):
        required_resources = {
            2: {'linemate': 1},
            3: {'linemate': 1, 'deraumere': 1, 'sibur': 1},
            4: {'deraumere': 2, 'sibur': 1, 'mendiane': 2},
            5: {'linemate': 1, 'deraumere': 1, 'sibur': 2, 'mendiane': 1},
            6: {'linemate': 1, 'sibur': 2, 'mendiane': 1, 'phiras': 3},
            7: {'linemate': 1, 'sibur': 2, 'mendiane': 3, 'phiras': 1},
            8: {'linemate': 2, 'deraumere': 2, 'sibur': 2, 'mendiane': 2, 'phiras': 2, 'thystame': 1}
        }
        return required_resources.get(elevation, {})
    
    def update_resources(self, required_resources):
        for resource, count in required_resources.items():
            self.resources[resource] -= count

    def has_enough_resources(self, required_resources):
        for resource, count in required_resources.items():
            if self.resources.get(resource, 0) < count:
                return False
        return True




# Modify the code as per your game mechanics and server communication

# Define the neural network model
class QNetwork(tf.keras.Model):
    def __init__(self, state_size, action_size):
        super(QNetwork, self).__init__()
        self.dense1 = tf.keras.layers.Dense(16, activation='relu')
        self.dense2 = tf.keras.layers.Dense(16, activation='relu')
        self.output_layer = tf.keras.layers.Dense(action_size)

    def call(self, state):
        x = self.dense1(state)
        x = self.dense2(x)
        q_values = self.output_layer(x)
        return q_values

# Define what action we do based on the int we got
def set_action(action):
    tab = [
        'Forward\n',
        'Right\n',
        'Left\n',
        'Fork\n',
        'Eject\n',
        'Incantation\n',
        'Set linemate\n',
        'Set deraumere\n',
        'Set sibur\n',
        'Set mendiane\n',
        'Set phiras\n',
        'Set thystame\n',
        'Take food\n',
        'Take linemate\n',
        'Take deraumere\n',
        'Take sibur\n',
        'Take mendiane\n',
        'Take phiras\n',
        'Take thystame\n'
    ]

    return tab[action]

# Initialize the game environment and neural network
def main():
    parser = Parsing()
    parser.error_handing()
    parser.run()

    port = parser.get_port()
    name = parser.get_name()
    machine = parser.get_machine()

    # Define the training loop
    for episode in range(10):
        # Create Communication
        sock = Communication(port, machine)

        if check_message_send(sock, name, machine, port) == False:
            print("Error: problem with the server")
            sys.exit(84)

        infos = sock.receive_message(port, machine)
        # infos2 = sock.receive_message()
        lines = infos.strip().split("\n")
        client_num = int(lines[0])
        x, y = map(int, lines[1].split())


        action_choose = ClientData(name, client_num, x, y, sock, port, machine)
        env = GameEnvironment(action_choose)

        state_size = 19
        action_size = 19
        model = QNetwork(state_size, action_size)

        # Define the hyperparameters and training settings
        epsilon = 1.0  # Exploration rate
        epsilon_decay = 0.995  # Decay rate for exploration
        gamma = 0.99  # Discount factor for future rewards
        optimizer = tf.keras.optimizers.legacy.Adam()
        loss_function = tf.keras.losses.MeanSquaredError()

        state = env.get_state()
        total_reward = 0

        while not env.is_done():
            test = 0
            map_game = action_choose.look()
            inv = action_choose.inventory()
            resources = re.findall(r'(\w+) (\d+)', inv)

            # Create a new dictionary to store the updated resources
            new_resources = {}

            # Iterate over the resource pairs
            for resource_name, resource_value in resources:
                new_resources[resource_name] = int(resource_value)

            # Update the self.resources dictionary with the new resources
            env.resources.update(new_resources)
            # Choose an action based on the epsilon-greedy strategy
            if np.random.rand() <= epsilon:
                action = np.random.randint(action_size)
                print("====================================== Action: " + str(action))
            else:
                q_values = model(np.expand_dims(state, 0))
                action = np.argmax(q_values[0])
                test = 1

            action = set_action(action)

            # Take the chosen action and observe the next state and reward
            env.take_action(action)
            next_state = env.get_state()
            reward = env.get_reward()

            # Calculate the target Q-values
            q_values_next = model(np.expand_dims(next_state, 0))
            max_q_value = np.max(q_values_next[0])
            if (test == 1):
                target_q_values = q_values[0]
                target_q_values[action] = reward + gamma * max_q_value

                # Train the neural network using the target Q-values
                with tf.GradientTape() as tape:
                    q_values_pred = model(np.expand_dims(state, 0))
                    loss = loss_function(target_q_values, q_values_pred)

                gradients = tape.gradient(loss, model.trainable_variables)
                optimizer.apply_gradients(zip(gradients, model.trainable_variables))

            state = next_state
            total_reward += reward
            print("Reward:", reward, "Action:", action, "Total Reward:", total_reward, "Episode:", episode)
            time.sleep(1)

        # Update the exploration rate
        print("======== I'M DEAD DABUDIDABUDA LALALILALALA")
        sock.close()
        env.resources['food'] = 10
        epsilon *= epsilon_decay

        # Print the total reward achieved in the episode
        print("Episode:", episode, "Total Reward:", total_reward)

    # Use the trained model for testing or further gameplay

if __name__ == '__main__':
    main()