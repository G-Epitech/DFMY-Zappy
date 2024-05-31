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

class Hamster:
    def __init__(self, client: SocketClient, name: str, map_size: tuple, add_hamster: Callable[[], None], ID: int):
        self.client: SocketClient = client
        self.name: str = name
        self.map_size: tuple = map_size
        self.add_hamster: Callable[[], None] = add_hamster
        self.ID: int = ID
        self.inventory = {
            "food": 0,
            "linemate": 0,
            "deraumere": 0,
            "sibur": 0,
            "mendiane": 0,
            "phiras": 0,
            "thystame": 0
        }
        self.pending_broadcast: list[tuple[int, str]] = []
        self.starting_timestamp = 0

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
                    response = response.split(",")
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
        self.client.send(f"Broadcast {message}\n")
        response = None
        while not response:
            response = self.client.receive()
        if response == "ko":
            self.debug(f"Server did not accept broadcast message: {message}")
        else:
            self.debug(f"Messaged successfully broadcasted")
    
    def get_current_time_nano(self) -> int:
        return int(datetime.now().timestamp() * 1000000000)
    
    def create_broadcast_message(self, message: str) -> str:
        message = {
            "starting_timestamp": self.starting_timestamp,
            "current_timestamp": self.get_current_time_nano(),
            "inventory": self.inventory,
            "message": message
        }
        return json.dumps(message)

    def run(self):
        self.debug(f"Hamster {self.name} is running")
        self.starting_timestamp = self.get_current_time_nano()
        print(self.create_broadcast_message("Hello"))
        while True:
            if self.ID == 1:
                self.update_inventory()
                # self.debug(f"Inventory: {self.inventory}")
            else:
                self.send_broadcast("Hello")

    def debug(self, string: str):
        print(f"[{time.strftime('%H:%M:%S')}] Hamster {self.ID}: {string}")
