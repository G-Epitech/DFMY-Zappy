##
## EPITECH PROJECT, 2024
## zappy
## File description:
## app
##

from classes.process import SubProcess
import random

EXIT_SUCCESS = 0
EXIT_FAILURE = 84

class App:
    def __init__(self, host: str, port: int, name: str):
        self.host: str = host
        self.port: int = port
        self.name: str = name
        self.list_processes: list[SubProcess] = []


    def add_process(self):
        number = random.randint(1, 100)

        process = SubProcess(self.host, self.port, self.name, self.add_process, number)
        self.list_processes.append(process)
        process.start()

    def run(self) -> int:
        self.add_process()
        for process in self.list_processes:
            process.join()
        return EXIT_SUCCESS
