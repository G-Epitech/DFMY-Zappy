##
## EPITECH PROJECT, 2024
## zappy
## File description:
## hamster
##

from classes.client import SocketClient
from typing import Callable

class Hamster:
    def __init__(self, client: SocketClient, name: str, map_size: tuple, add_hamster: Callable[[], None]):
        self.client: SocketClient = client
        self.name: str = name
        self.map_size: tuple = map_size
        self.add_hamster: Callable[[], None] = add_hamster

    def run(self):
        print(f"Hamster {self.name} is running")
        print(f"Map size: {self.map_size[0]}, {self.map_size[1]}")
        return
