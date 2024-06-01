##
## EPITECH PROJECT, 2024
## zappy
## File description:
## process
##

import time
import multiprocessing
from datetime import datetime
from classes.client import SocketClient
from typing import Callable
from classes.hamster import Hamster

EXIT_SUCCESS = 0
EXIT_FAILURE = 84

class SubProcess(multiprocessing.Process):
    def __init__(self, host: str, port: int, name: str, add_subprocess: Callable[[], None], ID: int):
        super(SubProcess, self).__init__()
        self.host: str = host
        self.port: int = port
        self.name: str = name
        self.client: SocketClient = SocketClient(self.host, self.port)
        self.add_subprocess: Callable[[], None] = add_subprocess
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
                    # self.debug(f"Server did not accept me, received: {response}")
                    self.client.close()
                    continue

                available_clients = int(response)

                if available_clients > 0:
                    self.add_subprocess()

                response = None
                while not response:
                    response = self.client.receive()
                
                self.debug(f"Successfully joined team {self.name}")

                map_size = tuple(map(int, response.split()))

                hamster = Hamster(self.client, self.name, map_size, self.add_subprocess, self.ID)

                hamster.run()

                self.client.close()
            except Exception as e:
                self.debug(f"An error occured: {e}")
                time.sleep(1)
            self.debug(f"I'm leaving the team")

    def debug(self, string: str):
        now = datetime.now()
        timestamp = now.strftime('%H:%M:%S') + f".{now.microsecond // 10:05d}"
        id_formate = f"{self.ID:02d}"
        print(f"[{timestamp}] Hamster {id_formate}: {string}")
