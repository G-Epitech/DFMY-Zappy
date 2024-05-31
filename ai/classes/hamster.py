##
## EPITECH PROJECT, 2024
## zappy
## File description:
## hamster
##

import time
from classes.client import SocketClient
from typing import Callable
import json
from datetime import datetime

HAMSTER_NEW = "NEW_HAMSTER"
HAMSTER_ASSERT_AUTHORITY = "I_AM_THE_MOTHER"
HAMSTER_CANNIBALISM = "I_WILL_EAT_YOU_"
HAMSTER_INCANTATION = "INCANTATION"
HAMSTER_OK = "OK"
HAMSTER_RUN = "RUN"

class Hamster:
    def __init__(self, client: SocketClient, name: str, map_size: tuple, add_hamster: Callable[[], None], ID: int):
        self.client: SocketClient = client
        self.name: str = name
        self.map_size: tuple = map_size
        self.add_hamster: Callable[[], None] = add_hamster
        self.ID: int = ID
        self.inventory = {
            "food": 9,
            "linemate": 0,
            "deraumere": 0,
            "sibur": 0,
            "mendiane": 0,
            "phiras": 0,
            "thystame": 0
        }
        self.pending_broadcast: list[tuple[int, str]] = []
        self.starting_timestamp = 0
        self.mother = True
        self.encryption_key = "MOTHER_HAMSTER_IS_THE_BEST"

    def get_response_from_last_command(self) -> str:
        response = None
        while not response:
            response = self.client.receive()
            if not response:
                continue
            if response.startswith("message "):
                try:
                    if len(response) <= len("message "):
                        raise Exception("Invalid message format")
                    response = response[len("message "):]
                    response = response.split(",", 1)
                    if len(response) != 2:
                        raise Exception("Invalid message format")
                    direction = int(response[0].strip())
                    message = response[1].strip()
                    self.pending_broadcast.append((direction, message))
                except Exception as e:
                    self.debug(f"Error parsing broadcast message: {e}")
                response = None
        return response

    def update_inventory(self):
        self.client.send("Inventory\n")
        response = self.get_response_from_last_command()
        try:
            if response == "ko":
                raise Exception("Server responded with ko")
            response = response.strip()
            if response.startswith("[") and response.endswith("]"):
                response = response[1:-1]
            inventory = response.split(",")
            if not inventory:
                raise Exception("Empty inventory")
            for item in inventory:
                if not item:
                    self.debug("Item is defined as None")
                    continue
                item = item.strip()
                if not item:
                    self.debug("Cannot strip item (remove leading/trailing spaces)")
                    continue
                item = item.split(" ")
                if not item:
                    self.debug("Cannot split item (remove spaces)")
                    continue
                if len(item) != 2:
                    self.debug(f"Item {item} is not in format [item_name item_quantity]")
                    continue
                if item[0] not in self.inventory:
                    self.debug(f"Item {item[0]} is not in inventory")
                    continue
                self.inventory[item[0]] = int(item[1])
        except Exception as e:
            self.debug(f"Error updating inventory: {e}")

    def send_broadcast(self, message: str):
        self.client.send(f"Broadcast {self.encrypt_message(message)}\n")
        response = self.get_response_from_last_command()
        if response == "ko":
            self.debug(f"Server did not accept broadcast message: |{message}|")
        elif response == "ok":
            self.debug(f"Messaged successfully broadcasted")
        else:
            self.debug(f"Server responded with unknown message: {response}")

    def get_current_time_nano(self) -> int:
        return int(datetime.now().timestamp() * 1000000000)

    def create_broadcast_message(self, message: str) -> str:
        json_message = {
            "starting_timestamp": self.starting_timestamp,
            "current_timestamp": self.get_current_time_nano(),
            "inventory": self.inventory,
            "message": message
        }
        message = json.dumps(json_message)
        message = message.replace(" ", "").replace("\"", "'")
        return message

    def manage_broadcast_message(self, message: str):
        message = self.decrypt_message(message)
        message = message.replace("'", "\"")
        message = json.loads(message)
        if not message:
            raise Exception(f"Invalid message format: {message}")
        if message["message"] == HAMSTER_NEW:
            if self.mother:
                if message["starting_timestamp"] > self.starting_timestamp:
                    self.send_broadcast(f"{self.create_broadcast_message(HAMSTER_ASSERT_AUTHORITY)}\n")
                else:
                    self.mother = False

    def manage_broadcast(self):
        for message in self.pending_broadcast:
            try:
                self.manage_broadcast_message(message[1])
            except Exception as e:
                self.debug(f"Error managing broadcast message: {e}")
        self.pending_broadcast = []

    def run(self):
        self.debug(f"Hamster {self.name} is running")
        self.starting_timestamp = self.get_current_time_nano()
        new_message = self.create_broadcast_message(HAMSTER_NEW)
        self.send_broadcast(new_message)
        while True:
            self.update_inventory()
            self.manage_broadcast()
            if self.mother:
                self.debug("I'm the mother")
            else:
                self.debug("I'm not the mother")

    def encrypt_message(self, message: str) -> str:
        encrypted_message = ""
        key_index = 0
        for char in message:
            if char.isalpha():
                key_char = self.encryption_key[key_index % len(self.encryption_key)]
                if char.isupper():
                    encrypted_char = chr((ord(char) + ord(key_char) - 2 * ord('A')) % 26 + ord('A'))
                else:
                    encrypted_char = chr((ord(char) + ord(key_char) - 2 * ord('a')) % 26 + ord('a'))
                encrypted_message += encrypted_char
                key_index += 1
            else:
                encrypted_message += char
        return encrypted_message
    
    def decrypt_message(self, message: str) -> str:
        decrypted_message = ""
        key_index = 0
        for char in message:
            if char.isalpha():
                key_char = self.encryption_key[key_index % len(self.encryption_key)]
                if char.isupper():
                    decrypted_char = chr((ord(char) - ord(key_char) + 26) % 26 + ord('A'))
                else:
                    decrypted_char = chr((ord(char) - ord(key_char) + 26) % 26 + ord('a'))
                decrypted_message += decrypted_char
                key_index += 1
            else:
                decrypted_message += char
        return decrypted_message

    def debug(self, string: str):
        print(f"[{time.strftime('%H:%M:%S')}] Hamster {self.ID}: {string}")
