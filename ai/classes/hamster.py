##
## EPITECH PROJECT, 2024
## zappy
## File description:
## hamster
##

import time
from classes.client import SocketClient
from typing import Any, Callable
import json
from datetime import datetime
import random
import time

HAMSTER_NEW = "NEW_HAMSTER"
HAMSTER_ASSERT_AUTHORITY = "I_AM_THE_MOTHER"
HAMSTER_CANNIBALISM = "I_WILL_EAT_YOU"
HAMSTER_REQUEST_CANNIBALISM = "MAY_I_EAT_YOU?"
HAMSTER_INCANTATION = "INCANTATION"
HAMSTER_OK = "OK"
HAMSTER_KO = "KO"
HAMSTER_RUN = "RUN"

ENCRYPTION_KEY= "MOTHER_HAMSTER_IS_THE_BEST"

COLOR_GREEN = "\033[1;32m"
COLOR_RED = "\033[1;31m"
COLOR_YELLOW = "\033[1;33m"
COLOR_BLUE = "\033[1;34m"
COLOR_MAGENTA = "\033[1;35m"
COLOR_CYAN = "\033[1;36m"
COLOR_RESET = "\033[0m"

class Hamster:
    def __init__(self, client: SocketClient, name: str, map_size: tuple, add_hamster: Callable[[], None], ID: int):
        self.client: SocketClient = client
        self.name: str = name
        self.map_size: tuple = map_size
        self.add_hamster: Callable[[], None] = add_hamster
        self.ID: int = ID
        self.inventory: dict = {
            "food": 9,
            "linemate": 0,
            "deraumere": 0,
            "sibur": 0,
            "mendiane": 0,
            "phiras": 0,
            "thystame": 0
        }
        self.pending_broadcast: list[tuple[int, str]] = []
        self.starting_timestamp: int = 0
        self.mother: bool = True
        self.hamsters: list[int] = []
        self.cannibal_parent: int = 0
        self.dead: bool = False
        self.sync_with_other_hamsters: bool = False

    def init_hamster(self):
        try:
            self.starting_timestamp = self.get_current_time_nano()
            new_message = self.create_broadcast_message(HAMSTER_NEW, 0)
            self.send_broadcast(new_message)
        except Exception as e:
            self.debug(f"Error running hamster: {e}")
    
    def response_get_broadcast_message(self, response: str) -> tuple[int, str] | None:
        if response.startswith("message "):
            try:
                if len(response) <= len("message "):
                    raise Exception("Invalid message format")
                response = response[len("message "):]
                direction, message = response.split(",", 1)
                direction_int = int(direction.strip())
                message = message.strip()
                return (direction_int, message)
            except Exception as e:
                self.debug(f"Error parsing broadcast message: {e}")
        return None

    def response_get_last_command(self) -> str:
        response = None
        while not response:
            response = self.client.receive()
            if not response:
                continue
            if response == "dead":
                self.dead = True
                return response
            if response.startswith("message "):
                broadcast_message = self.response_get_broadcast_message(response)
                if broadcast_message:
                    self.pending_broadcast.append(broadcast_message)
                response = None
        return response
    
    def response_get_array(self, response: str) -> list[str] | None:
        try:
            response = response.strip()
            if response.startswith("[") and response.endswith("]"):
                response = response[1:-1]
            else:
                raise Exception("Invalid array format, must be in format [item1, item2, ...]")
            list = response.split(",")
            if not response:
                raise Exception("Empty array")
            return list
        except Exception as e:
            self.debug(f"Error parsing array: {e}")
        return None

    def update_inventory(self):
        try:
            self.client.send("Inventory\n")
            response = self.response_get_last_command()
            if response == "ko":
                raise Exception("Server responded with ko")
            inventory = self.response_get_array(response)
            if not inventory:
                raise Exception("Invalid inventory format")
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
        response = self.response_get_last_command()
        if response == "ko":
            self.debug(f"Server did not accept broadcast message: |{message}|")
        elif response == "ok":
            self.debug(f"Messaged successfully broadcasted")
        else:
            self.debug(f"Server responded with unknown message: {response}")

    def get_current_time_nano(self) -> int:
        return int(datetime.now().timestamp() * 1000000000)

    def create_broadcast_message(self, message: str, recipient: int) -> str:
        json_message = {
            "starting_timestamp": self.starting_timestamp,
            "current_timestamp": self.get_current_time_nano(),
            "inventory": self.inventory,
            "message": message,
            "recipient": recipient
        }
        message = json.dumps(json_message)
        message = message.replace(" ", "").replace("\"", "'")
        return message

    def manage_broadcast_message(self, dir: int, message: str):
        message = self.decrypt_message(message).replace("'", "\"")
        json_message = json.loads(message)
        if not message:
            raise Exception(f"Invalid message format: {message}")
        if json_message["message"] == HAMSTER_NEW:
            if self.mother:
                if json_message["starting_timestamp"] > self.starting_timestamp:
                    self.send_broadcast(f"{self.create_broadcast_message(HAMSTER_ASSERT_AUTHORITY, json_message['starting_timestamp'])}")
                    self.sync_with_other_hamsters = True
                else:
                    self.mother = False
                    self.sync_with_other_hamsters = True
        if json_message["message"] == HAMSTER_ASSERT_AUTHORITY:
            self.mother = False
            self.sync_with_other_hamsters = True
        if json_message["message"] == HAMSTER_CANNIBALISM:
            if json_message["recipient"] == self.starting_timestamp:
                if self.cannibal_parent == 0 and dir == 0:
                    self.sync_with_other_hamsters = True
                    self.cannibal_parent = json_message["starting_timestamp"]
                    self.send_broadcast(f"{self.create_broadcast_message(HAMSTER_OK, json_message['starting_timestamp'])}")
                    self.debug(f"Accepted cannibalism from {json_message['starting_timestamp']}")
                else:
                    self.send_broadcast(f"{self.create_broadcast_message(HAMSTER_KO, json_message['starting_timestamp'])}")

    def manage_broadcast(self):
        for message in self.pending_broadcast:
            try:
                self.manage_broadcast_message(message[0], message[1])
            except Exception as e:
                self.debug(f"Error managing broadcast message: {e}")
        self.pending_broadcast = []

    def message_get_json(self, message: str) -> Any | None:
        try:
            unparsed_message = self.decrypt_message(message).replace("'", "\"")
            json_message = json.loads(unparsed_message)
            return json_message
        except Exception as e:
            self.debug(f"Error parsing broadcast message: {e}")
        return None
    
    def json_get_sender(self, json_message: Any) -> int | None:
        try:
            return json_message["starting_timestamp"]
        except Exception as e:
            self.debug(f"Error getting sender from json message: {e}")
        return None
    
    def canniablism_get_new_hamster_id(self, message: str) -> int | None:
        json_message = self.message_get_json(message)
        if not json_message:
            return None
        sender_id = self.json_get_sender(json_message)
        if not sender_id:
            return None
        if json_message["message"] == HAMSTER_NEW:
            return sender_id
        return None

    def canniablism_find_new_hamster_from_pending_broadcast(self) -> int | None:
        for message in self.pending_broadcast:
            try:
                child_hamster = self.canniablism_get_new_hamster_id(message[1])
                if child_hamster:
                    self.pending_broadcast.remove(message)
                    return child_hamster
            except Exception as e:
                self.debug(f"Error parsing broadcast message: {e}")
        return None

    def cannibalism_fetch_new_hamster_id(self) -> int:

        while True:
            response = self.client.receive()
            if not response:
                continue
            if response.startswith("message "):
                try:
                    broadcast_message = self.response_get_broadcast_message(response)
                    if broadcast_message:    
                        try:
                            json_message = self.message_get_json(broadcast_message[1])
                            if not json_message:
                                raise Exception("Invalid json message")
                            if json_message["message"] == HAMSTER_NEW:
                                child_hamster = json_message["starting_timestamp"]
                                return child_hamster
                        except Exception as e:
                            self.debug(f"Error parsing broadcast message: {e}")
                        self.pending_broadcast.append(broadcast_message)
                except Exception as e:
                    self.debug(f"Error parsing broadcast message: {e}")
                response = None

    def cannibalism_accepted(self) -> bool:
        response = None
        accepted = False

        while True:
            response = self.client.receive()
            if not response:
                continue
            if response.startswith("message "):
                try:
                    broadcast_message = self.response_get_broadcast_message(response)
                    if broadcast_message:
                        try:
                            json_message = self.message_get_json(broadcast_message[1])
                            if json_message and json_message["recipient"] == self.starting_timestamp:
                                if json_message["message"] == HAMSTER_OK:
                                    accepted = True
                                    break
                                elif json_message["message"] == HAMSTER_KO:
                                    accepted = False
                                    break
                        except Exception as e:
                            self.debug(f"Error parsing broadcast message: {e}")
                        self.pending_broadcast.append(broadcast_message)
                except Exception as e:
                    self.debug(f"Error parsing broadcast message: {e}")
                response = None
        return accepted

    def cannibalism(self):
        self.cannibal_parent = self.starting_timestamp

        self.client.send(f"Fork\n")
        response = self.response_get_last_command()
        if response == "ko":
            self.debug("Server did not accept fork")
            return
        elif response == "ok":
            self.debug("Fork accepted")
        else:
            self.debug(f"Server responded with unknown message: {response}")
            return

        self.add_hamster()

        find_my_child = False

        while not find_my_child:
            child_hamster = 0
            child_hamster = self.canniablism_find_new_hamster_from_pending_broadcast()
            if not child_hamster:
                child_hamster = self.cannibalism_fetch_new_hamster_id()

            self.debug(f"Child hamster: {child_hamster}")

            self.send_broadcast(f"{self.create_broadcast_message(HAMSTER_CANNIBALISM, child_hamster)}")

            accepted = self.cannibalism_accepted()

            if accepted:
                self.debug(f"Cannibalism accepted by child {child_hamster}")
                find_my_child = True
            else:
                self.debug(f"Cannibalism refused by child {child_hamster}")

        attempt = 0

        while True:
            try:
                food_on_ground = 0
                self.client.send(f"Look\n")
                response = self.response_get_last_command()
                if response == "ko":
                    self.error("Server did not accept look")
                    return
                self.debug(f"Look response: {response}")
                vision = self.response_get_array(response)
                if not vision:
                    raise Exception("Invalid vision format")         
                first_case = vision[0].strip()
                first_case_list = first_case.split(" ")
                if not first_case_list:
                    raise Exception("Invalid first element in vision")
                self.debug(f"First case: {first_case_list}", COLOR_BLUE)
                for item in first_case_list:
                    if item == "food":
                        food_on_ground += 1
                self.debug(f"Food on ground: {food_on_ground}")
                if food_on_ground > 0:
                    while food_on_ground > 0:
                        self.client.send(f"Take food\n")
                        response = self.response_get_last_command()
                        if response == "ko":
                            self.debug("Server did not accept take food")
                        elif response == "ok":
                            self.debug("Took food")
                        else:
                            self.debug(f"Server responded with unknown message: {response}")
                            return
                        food_on_ground -= 1
                else:
                    self.debug("No food on ground")
                    if attempt > 2:
                        break
                    attempt += 1
            except Exception as e:
                self.error(f"Error cannibalism: {e}")

    def run(self):
        self.debug(f"Hamster {self.name} is running")
        self.init_hamster()

        while not self.sync_with_other_hamsters and not self.dead:
            try:
                for _ in range(10):
                    self.update_inventory()
                self.manage_broadcast()
            except Exception as e:
                self.debug(f"An error occured in the main loop: {e}")

        self.debug(f"Hamster {self.name} is now synchronized! Am I ? { self.cannibal_parent > 0 and self.cannibal_parent != self.starting_timestamp } ; ID: { self.starting_timestamp }", COLOR_GREEN)

        while not self.dead:
            try:
                self.manage_broadcast()
                if self.cannibal_parent > 0 and self.cannibal_parent != self.starting_timestamp:
                    self.debug(f"Parent cannibal: {self.cannibal_parent}")
                    self.client.send(f"Set food\n")
                    response = self.response_get_last_command()
                    if response == "ko":
                        self.debug("Server did not accept set food")
                    elif response == "dead":
                        self.debug("Server responded with dead")
                else:
                    self.update_inventory()
                    self.debug(f"Inventory: {self.inventory}")
                    if self.inventory["food"] < 20:
                        self.debug("I'm hungry")
                        for _ in range(10):
                            self.cannibalism()
                            # self.update_inventory()
                            # self.debug(f"Inventory: {self.inventory}")
                            self.manage_broadcast()
                            self.error("Less hungry")
                        self.error("I'm not hungry anymore!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!")
                self.manage_broadcast()
            except Exception as e:
                self.debug(f"An error occured in the main loop: {e}")

    def encrypt_message(self, message: str) -> str:
        encrypted_message = ""
        key_index = 0
        for char in message:
            if char.isalpha():
                key_char = ENCRYPTION_KEY[key_index % len(ENCRYPTION_KEY)]
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
                key_char = ENCRYPTION_KEY[key_index % len(ENCRYPTION_KEY)]
                if char.isupper():
                    decrypted_char = chr((ord(char) - ord(key_char) + 26) % 26 + ord('A'))
                else:
                    decrypted_char = chr((ord(char) - ord(key_char) + 26) % 26 + ord('a'))
                decrypted_message += decrypted_char
                key_index += 1
            else:
                decrypted_message += char
        return decrypted_message

    def debug(self, string: str, color: str = COLOR_RESET):
        now = datetime.now()
        timestamp = now.strftime('%H:%M:%S') + f".{now.microsecond // 10:05d}"
        id_formate = f"{self.ID:03d}"
        print(f"{color}[{timestamp}] Hamster {id_formate}: {string}{COLOR_RESET}")

    def error(self, string: str):
        now = datetime.now()
        timestamp = now.strftime('%H:%M:%S') + f".{now.microsecond // 10:05d}"
        id_formate = f"{self.ID:03d}"
        print(f"{COLOR_RED}[{timestamp}] Hamster {id_formate}: {string}{COLOR_RESET}")
