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
        self.pending_cannibal_parent: list[int] = 0
        self.cannibal_parent: int = 0
        self.dead: bool = False
        self.sync_with_other_hamsters: bool = False

    def get_response_from_last_command(self) -> str:
        response = None
        while not response:
            response = self.client.receive()
            if not response:
                continue
            if response == "dead":
                self.dead = True
                return response
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
        try:
            self.client.send("Inventory\n")
            response = self.get_response_from_last_command()
            if response == "ko":
                raise Exception("Server responded with ko")
            response = response.strip()
            if response.startswith("[") and response.endswith("]"):
                response = response[1:-1]
            else:
                raise Exception("Invalid inventory format, must be in format [item_name item_quantity, ...]")
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
        message = self.decrypt_message(message)
        message = message.replace("'", "\"")
        message = json.loads(message)
        if not message:
            raise Exception(f"Invalid message format: {message}")
        if message["message"] == HAMSTER_NEW:
            if self.mother:
                if message["starting_timestamp"] > self.starting_timestamp:
                    self.send_broadcast(f"{self.create_broadcast_message(HAMSTER_ASSERT_AUTHORITY, message['starting_timestamp'])}")
                    self.sync_with_other_hamsters = True
                else:
                    self.mother = False
                    self.sync_with_other_hamsters = True
        if message["message"] == HAMSTER_ASSERT_AUTHORITY:
            self.mother = False
            self.sync_with_other_hamsters = True
        if message["message"] == HAMSTER_CANNIBALISM:
            if message["recipient"] == self.starting_timestamp:
                if self.cannibal_parent == 0 and dir == 0:
                    self.sync_with_other_hamsters = True
                    self.cannibal_parent = message["starting_timestamp"]
                    self.send_broadcast(f"{self.create_broadcast_message(HAMSTER_OK, message['starting_timestamp'])}")
                    self.debug(f"Accepted cannibalism from {message['starting_timestamp']}")
                else:
                    self.send_broadcast(f"{self.create_broadcast_message(HAMSTER_KO, message['starting_timestamp'])}")

    def manage_broadcast(self):
        for message in self.pending_broadcast:
            try:
                self.manage_broadcast_message(message[0], message[1])
            except Exception as e:
                self.debug(f"Error managing broadcast message: {e}")
        self.pending_broadcast = []
    
    def canniablism_find_new_hamster_from_pending_broadcast(self) -> int:
        child_hamster: int = 0
        for message in self.pending_broadcast:
            try:
                json_message = self.decrypt_message(message[1])
                json_message = json_message.replace("'", "\"")
                json_message = json.loads(json_message)
                if json_message["message"] == HAMSTER_NEW:
                    child_hamster = json_message["starting_timestamp"]
                    break
            except Exception as e:
                self.debug(f"Error parsing broadcast message: {e}")
        return child_hamster

    def cannibalism_fetch_new_hamster_id(self) -> int:
        child_hamster: int = 0
        response = None
        while not response or child_hamster == 0:
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
                    try:
                        json_message = self.decrypt_message(message)
                        json_message = json_message.replace("'", "\"")
                        json_message = json.loads(json_message)
                        if json_message["message"] == HAMSTER_NEW:
                            child_hamster = json_message["starting_timestamp"]
                            break
                    except Exception as e:
                        self.debug(f"Error parsing broadcast message: {e}")
                    self.pending_broadcast.append((direction, message))
                except Exception as e:
                    self.debug(f"Error parsing broadcast message: {e}")
                response = None
        return child_hamster

    def cannibalism_accepted(self) -> bool:
        response = None
        accepted = False

        while True:
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
                    try:
                        json_message = self.decrypt_message(message)
                        json_message = json_message.replace("'", "\"")
                        json_message = json.loads(json_message)
                        if json_message["recipient"] == self.starting_timestamp:
                            if json_message["message"] == HAMSTER_OK:
                                accepted = True
                                break
                            elif json_message["message"] == HAMSTER_KO:
                                accepted = False
                                break
                    except Exception as e:
                        self.debug(f"Error parsing broadcast message: {e}")
                    self.pending_broadcast.append((direction, message))
                except Exception as e:
                    self.debug(f"Error parsing broadcast message: {e}")
                response = None
        return accepted

    def cannibalism(self):
        self.cannibal_parent = self.starting_timestamp

        self.client.send(f"Fork\n")
        response = self.get_response_from_last_command()
        if response == "ko":
            self.debug("Server did not accept fork")
            return
        elif response == "ok":
            self.debug("Fork accepted")
        else:
            self.debug(f"Server responded with unknown message: {response}")
            return
        
        # connect_nbr = 0
        
        # while connect_nbr == 0:
        #     self.client.send(f"Connect_nbr\n")
        #     response = self.get_response_from_last_command()
        #     if response == "ko":
        #         self.debug("Server did not accept connect_nbr")
        #         return
        #     elif response == "dead":
        #         self.debug("Server responded with dead")
        #         return
        #     connect_nbr = int(response)
        
        # self.debug(f"Connect_nbr: {connect_nbr}")

        self.add_hamster()

        find_my_child = False

        while not find_my_child:
            child_hamster: int = 0
            child_hamster: int = self.canniablism_find_new_hamster_from_pending_broadcast()
            if child_hamster == 0:
                child_hamster: int = self.cannibalism_fetch_new_hamster_id()

            self.debug(f"Child hamster: {child_hamster}")

            self.send_broadcast(f"{self.create_broadcast_message(HAMSTER_CANNIBALISM, child_hamster)}")

            accepted: bool = self.cannibalism_accepted()

            if accepted:
                self.debug(f"Cannibalism accepted by child {child_hamster}")
                find_my_child = True
            else:
                self.debug(f"Cannibalism refused by child {child_hamster}")
        
        attempt = 0
        
        while True:
            food_on_ground = 0
            self.client.send(f"Look\n")
            response = self.get_response_from_last_command()
            if response == "ko":
                self.debug("Server did not accept look")
                return
            self.debug(f"Look response: {response}")
            response = response.strip()
            if response.startswith("[") and response.endswith("]"):
                response = response[1:-1]
            else:
                self.debug("Invalid look format")
                return
            response = response.split(",")
            if not response:
                self.debug("Empty look")
                return
            first = response[0].strip()
            first = first.split(" ")
            if not first:
                self.debug("Empty first")
                return
            for item in first:
                if item == "food":
                    food_on_ground += 1
            self.debug(f"Food on ground: {food_on_ground}")
            if food_on_ground > 0:
                self.client.send(f"Take food\n")
                response = self.get_response_from_last_command()
                if response == "ko":
                    self.debug("Server did not accept take food")
                    return
                elif response == "ok":
                    self.debug("Took food")
                else:
                    self.debug(f"Server responded with unknown message: {response}")
                    return
            else:
                self.debug("No food on ground")
                if attempt > 5:
                    break
                attempt += 1

    def init_hamster(self):
        sended = False
        while not sended:
            try:
                self.starting_timestamp = self.get_current_time_nano()
                new_message = self.create_broadcast_message(HAMSTER_NEW, 0)
                self.send_broadcast(new_message)
                sended = True
            except Exception as e:
                self.debug(f"Error running hamster: {e}")

    def run(self):
        delay_time = 15

        self.debug(f"Hamster {self.name} is running")
        self.init_hamster()

        while not self.sync_with_other_hamsters and not self.dead:
            try:
                self.update_inventory()
                self.manage_broadcast()
            except Exception as e:
                self.debug(f"An error occured in the main loop: {e}")

        self.debug(f"Hamster {self.name} is now synchronized! Am I ? { self.cannibal_parent > 0 and self.cannibal_parent != self.starting_timestamp }")

        while not self.dead:
            try:
                # while delay_time > 0:
                #     self.update_inventory()
                #     self.debug(f"Inventory: {self.inventory}")
                #     delay_time -= 1
                self.manage_broadcast()
                if self.cannibal_parent > 0 and self.cannibal_parent != self.starting_timestamp:
                    self.debug(f"Parent cannibal: {self.cannibal_parent}")
                    self.client.send(f"Set food\n")
                    response = self.get_response_from_last_command()
                    if response == "ko":
                        self.debug("Server did not accept set food")
                    elif response == "dead":
                        self.debug("Server responded with dead")
                else:
                    self.update_inventory()
                    self.debug(f"Inventory: {self.inventory}")
                    if self.inventory["food"] < 20:
                        self.debug("I'm hungry")
                        self.cannibalism()
                        self.debug("I'm not hungry anymore!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!")
                    # if self.mother:
                    #     self.debug("I'm the mother")
                    #     self.debug(f"Inventory: {self.inventory}")
                    # else:
                    #     self.debug("I'm not the mother")
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

    def debug(self, string: str):
        now = datetime.now()
        timestamp = now.strftime('%H:%M:%S') + f".{now.microsecond // 10:05d}"
        id_formate = f"{self.ID:03d}"
        print(f"[{timestamp}] Hamster {id_formate}: {string}")
