##
## EPITECH PROJECT, 2024
## zappy
## File description:
## app
##

from classes.process import SubProcess

EXIT_SUCCESS = 0
EXIT_FAILURE = 84

class App:
    def __init__(self, host: str, port: int, name: str):
        self.host: str = host
        self.port: int = port
        self.name: str = name
        self.list_processes: list[SubProcess] = []

    def add_process(self):
        process = SubProcess(self.host, self.port, self.name, self.add_process)
        process.start()
        self.list_processes.append(process)
        print(f"Process {self.name} started")

    def run(self) -> int:
        self.add_process()
        # self.add_process()
        for process in self.list_processes:
            process.join()
        return EXIT_SUCCESS
