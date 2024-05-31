##
## EPITECH PROJECT, 2024
## zappy
## File description:
## hamster
##

import time
from classes.client import SocketClient
from typing import Callable

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

    def update_inventory(self):
        self.client.send("Inventory\n")
        response = None
        while not response:
            response = self.client.receive()
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

    def run(self):
        print(f"Hamster {self.name} is running")
        while True:
            self.update_inventory()
            self.debug(f"Inventory: {self.inventory}")

    def debug(self, string: str):
        print(f"[{time.strftime('%H:%M:%S')}] Hamster {self.ID}: {string}")
