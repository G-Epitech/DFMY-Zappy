##
## EPITECH PROJECT, 2024
## zappy
## File description:
## app
##

from classes.thread import Thread
import random

import threading

EXIT_SUCCESS = 0
EXIT_FAILURE = 84

class App:
    def __init__(self, host: str, port: int, name: str):
        self.host: str = host
        self.port: int = port
        self.name: str = name
        self.list_threads: list[threading.Thread] = []

    def add_thread(self):
        number = random.randint(0, 999)

        thread = threading.Thread(target=Thread(self.host, self.port, self.name, self.add_thread, number).run)
        self.list_threads.append(thread)
        thread.start()

    def run(self) -> int:
        self.add_thread()
        for thread in self.list_threads:
            thread.join()
        return EXIT_SUCCESS
