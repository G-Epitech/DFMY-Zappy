##
## EPITECH PROJECT, 2024
## zappy
## File description:
## process
##

import time
from datetime import datetime
from classes.client import SocketClient
from typing import Callable
from classes.hamster import Hamster

EXIT_SUCCESS = 0
EXIT_FAILURE = 84

COLOR_GREEN = "\033[1;32m"
COLOR_RED = "\033[1;31m"
COLOR_YELLOW = "\033[1;33m"
COLOR_BLUE = "\033[1;34m"
COLOR_MAGENTA = "\033[1;35m"
COLOR_CYAN = "\033[1;36m"
COLOR_RESET = "\033[0m"

class Thread():
    def __init__(self, host: str, port: int, name: str, add_thread: Callable[[], None], ID: int):
        self.host: str = host
        self.port: int = port
        self.name: str = name
        self.client: SocketClient = SocketClient(self.host, self.port)
        self.add_thread: Callable[[], None] = add_thread
        self.ID: int = ID

    def run(self):
        self.debug(f"Starting player in team {self.name}")
        while True:
            try:
                self.client.connect()

                response = None
                while not response:
                    response = self.client.receive()

                if response != "WELCOME":
                    self.debug(f"Server did not send WELCOME, received: {response}")
                    self.client.close()
                    continue

                self.client.send(f"{self.name}\n")

                response = None
                while not response:
                    response = self.client.receive()

                if response == "ko":
                    self.client.close()
                    time.sleep(0.2)
                    continue

                available_clients = int(response)

                if available_clients > 0:
                    self.add_thread()

                response = None
                while not response:
                    response = self.client.receive()

                self.debug(f"Successfully joined team {self.name}")

                map_size = tuple(map(int, response.split()))

                hamster = Hamster(self.client, self.name, map_size, self.add_thread, self.ID)

                hamster.run()

                self.client.close()
            except Exception as e:
                self.debug(f"An error occured: {e}")
                exit(EXIT_FAILURE)
            self.debug(f"I'm leaving the team", COLOR_MAGENTA)
            exit(EXIT_SUCCESS)

    def debug(self, string: str, color: str = COLOR_RESET):
        now = datetime.now()
        timestamp = now.strftime('%H:%M:%S') + f".{now.microsecond // 10:05d}"
        id_formate = f"{self.ID:03d}"
        print(f"{color}[{timestamp}] Hamster {id_formate}: {string}{COLOR_RESET}")
