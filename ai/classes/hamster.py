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
HAMSTER_INCANTATION = "INCANTATION"
HAMSTER_CALL_FAMILY = "CALL_FAMILY"
HAMSTER_COMMING = "COMMING"
HAMSTER_OK = "OK"
HAMSTER_KO = "KO"
HAMSTER_RUN = "RUN"

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
        self.encrypting_key: str = "I_AM_THE_MOTHER_OF_" + self.name
        self.called_by_mother: bool = False
        self.direction_called_by_mother: int = 0

    def init_hamster(self):
        """
        Initializes the hamster.

        This method sets the starting timestamp and sends a broadcast message to create a new hamster.
        """
        try:
            self.starting_timestamp = self.get_current_time_nano()
            new_message = self.create_broadcast_message(HAMSTER_NEW, 0)
            self.send_broadcast(new_message)
        except Exception as e:
            self.debug(f"Error running hamster: {e}")
    
    def response_get_broadcast_message(self, response: str) -> tuple[int, str] | None:
        """
        Parses a response string and extracts the broadcast message.

        Args:
            response (str): The response string to parse.

        Returns:
            tuple[int, str] | None: A tuple containing the direction (as an integer) and the message,
            or None if the response does not start with "message " or if there is an error parsing the message.
        """
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
        """
        Retrieves the last command response from the client.

        Returns:
            str: The last command response received from the client.
        """
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
        """
        Parses a string response and returns a list of items.

        Args:
            response (str): The string response to parse.

        Returns:
            list[str] | None: A list of items if the response is valid, None otherwise.
        """
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
        """
        Update the inventory of the hamster.

        This method sends a command to the server to retrieve the inventory,
        parses the response, and updates the hamster's inventory accordingly.
        """
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
        """
        Sends a broadcast message to the server.

        Args:
            message (str): The message to be broadcasted.
        """
        self.client.send(f"Broadcast {self.encrypt_message(message)}\n")
        response = self.response_get_last_command()
        if response == "ko":
            self.debug(f"Server did not accept broadcast message: |{message}|")
        elif response == "ok":
            self.debug(f"Message successfully broadcasted")
        else:
            self.debug(f"Server responded with unknown message: {response}")

    def get_current_time_nano(self) -> int:
            """
            Returns the current time in nanoseconds.

            Returns:
                int: The current time in nanoseconds.
            """
            return int(datetime.now().timestamp() * 1000000000)

    def create_broadcast_message(self, message: str, recipient: int) -> str:
        """
        Creates a broadcast message in JSON format.

        Args:
            message (str): The message to be included in the broadcast.
            recipient (int): The ID of the recipient.

        Returns:
            str: The broadcast message in JSON format.
        """
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
        """
        This function manages incoming broadcast messages.
        The steps involved are as follows:
    
        1. Decrypting and Parsing the Message:
            - Decrypts the incoming message using `self.decrypt_message(message)`.
            - Replaces single quotes with double quotes for JSON compatibility.
            - Attempts to parse the decrypted message as JSON using `json.loads(message)`.
    
        2. Handling Message Types:
            - Checks if the parsed JSON message is valid.
            - Checks the message type and performs specific actions accordingly.
    
        3. Handling "HAMSTER_NEW" Messages:
            - If the message type is "HAMSTER_NEW":
                - Checks if the current entity is a mother hamster.
                - Compares the starting timestamp of the new hamster with the current one.
                - If the new hamster has a higher timestamp and the current entity is a mother:
                    - Sends a broadcast to assert authority to the new hamster.
                    - Sets `self.sync_with_other_hamsters` to True.
                - If the new hamster has a lower or equal timestamp:
                    - Sets the current entity as not a mother hamster.
                    - Sets `self.sync_with_other_hamsters` to True.
    
        4. Handling "HAMSTER_ASSERT_AUTHORITY" Messages:
            - If the message type is "HAMSTER_ASSERT_AUTHORITY":
                - Sets the current entity as not a mother hamster.
                - Sets `self.sync_with_other_hamsters` to True.
    
        5. Handling "HAMSTER_CANNIBALISM" Messages:
            - If the message type is "HAMSTER_CANNIBALISM":
                - Checks if the recipient matches the current entity's starting timestamp.
                - If the current entity is not already a cannibal and it's the correct direction:
                    - Sets `self.sync_with_other_hamsters` to True.
                    - Records the sender's timestamp as the cannibal parent.
                    - Sends an acknowledgment broadcast to the sender.
                - Otherwise, sends a rejection broadcast to the sender.
    
        Parameters:
            - dir: The direction of the message.
            - message: The encrypted message received from the server.
        """
        message = self.decrypt_message(message).replace("'", "\"")
        json_message = json.loads(message)
        if not message:
            raise Exception(f"Invalid message format: {message}")
        if json_message["message"] == HAMSTER_NEW:
            if self.mother:
                if json_message["starting_timestamp"] > self.starting_timestamp:
                    self.error(f"New hamster {json_message['starting_timestamp']} is a mother")
                    self.send_broadcast(f"{self.create_broadcast_message(HAMSTER_ASSERT_AUTHORITY, json_message['starting_timestamp'])}")
                    self.sync_with_other_hamsters = True
                else:
                    self.mother = False
                    self.error(f"New hamster {json_message['starting_timestamp']} is not a mother")
                    self.sync_with_other_hamsters = True
        if json_message["message"] == HAMSTER_ASSERT_AUTHORITY:
            self.mother = False
            self.sync_with_other_hamsters = True
            self.error(f"New hamster {json_message['starting_timestamp']} is not a mother")
        if json_message["message"] == HAMSTER_CANNIBALISM:
            if json_message["recipient"] == self.starting_timestamp:
                if self.cannibal_parent == 0 and dir == 0:
                    self.mother = False
                    self.sync_with_other_hamsters = True
                    self.cannibal_parent = json_message["starting_timestamp"]
                    self.send_broadcast(f"{self.create_broadcast_message(HAMSTER_OK, json_message['starting_timestamp'])}")
                    self.debug(f"Accepted cannibalism from {json_message['starting_timestamp']}")
                else:
                    self.send_broadcast(f"{self.create_broadcast_message(HAMSTER_KO, json_message['starting_timestamp'])}")
        if json_message["message"] == HAMSTER_CALL_FAMILY:
            self.send_broadcast(f"{self.create_broadcast_message(HAMSTER_COMMING, json_message['starting_timestamp'])}")
            self.called_by_mother = True

    def manage_broadcast(self):
        """
        Process and manage pending broadcast messages.

        This method iterates over the list of pending broadcast messages and
        calls the `manage_broadcast_message` method for each message. If an
        error occurs while processing a message, it is caught and logged as a
        debug message.

        After processing all the pending messages, the list of pending
        broadcast messages is cleared.
        """
        for message in self.pending_broadcast:
            try:
                self.manage_broadcast_message(message[0], message[1])
            except Exception as e:
                self.debug(f"Error managing broadcast message: {e}")
        self.pending_broadcast = []

    def message_get_json(self, message: str) -> Any | None:
        """
        Parses a message string and returns the corresponding JSON object.

        Args:
            message (str): The message string to be parsed.

        Returns:
            Union[Any, None]: The parsed JSON object if successful, None otherwise.
        """
        try:
            unparsed_message = self.decrypt_message(message).replace("'", "\"")
            json_message = json.loads(unparsed_message)
            return json_message
        except Exception as e:
            self.debug(f"Error parsing broadcast message: {e}")
        return None
    
    def json_get_sender(self, json_message: Any) -> int | None:
        """
        Retrieves the sender from a JSON message.

        Args:
            json_message (Any): The JSON message.

        Returns:
            int | None: The sender ID if found, None otherwise.
        """
        try:
            return json_message["starting_timestamp"]
        except Exception as e:
            self.debug(f"Error getting sender from json message: {e}")
        return None
    
    def canniablism_get_new_hamster_id(self, message: str) -> int | None:
        """
        This function extracts a new hamster ID from a given message.
        The steps involved are as follows:

        1. Parsing the Message:
            - Attempts to parse the message as JSON using `self.message_get_json(message)`.

        2. Extracting Sender ID:
            - Checks if the JSON message is valid.
            - Extracts the sender ID from the JSON message using `self.json_get_sender(json_message)`.

        3. Extracting Hamster ID:
            - If the sender ID is valid and the message type is `HAMSTER_NEW`, returns the sender ID as the new hamster ID.

        4. Returning the Result:
            - Returns the new hamster ID if found; otherwise, returns `None`.
        """
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
        """
        This function searches through pending broadcast messages to find a new hamster ID.
        The steps involved are as follows:

        1. Iterating Over Pending Broadcasts:
            - Iterates over each message in `self.pending_broadcast`.

        2. Extracting Hamster ID:
            - Attempts to extract a new hamster ID from each message using `self.canniablism_get_new_hamster_id(message[1])`.
            - If a valid hamster ID is found, removes the message from `self.pending_broadcast`.
            - Returns the new hamster ID immediately if found.

        3. Handling Errors:
            - Handles any exceptions during message parsing and logs debug messages.

        4. Returning the Result:
            - If no new hamster ID is found in the pending broadcasts, returns `None`.
        """
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
        """
        This function continuously listens for broadcast messages from the server to fetch a new hamster ID.
        The steps involved are as follows:

        1. Receiving Server Responses:
            - Enters an infinite loop to receive responses from the server.
            - Continuously receives messages from the server using `self.client.receive()`.
            - If a response is received, processes the response.

        2. Processing Broadcast Messages:
            - Checks if the response starts with "message ".
            - Attempts to parse the broadcast message using `self.response_get_broadcast_message(response)`.
            - If a valid broadcast message is found, tries to convert the message to JSON using `self.message_get_json(broadcast_message[1])`.

        3. Extracting Hamster ID:
            - Checks if the JSON message is valid.
            - If the message type is `HAMSTER_NEW`, extracts the `starting_timestamp` as the new hamster ID.
            - Returns the new hamster ID immediately if found.

        4. Handling Errors and Pending Broadcasts:
            - Handles any exceptions during message parsing and logs debug messages.
            - Adds the broadcast message to `self.pending_broadcast` if it is not processed.
        """

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
        """
        This function checks if the cannibalism request has been accepted by a child hamster.
        The steps involved are as follows:

        1. Initialization:
            - Initializes `response` to None and `accepted` to False.

        2. Receiving Server Responses:
            - Enters an infinite loop to receive responses from the server.
            - Continuously receives messages from the server using `self.client.receive()`.
            - If a response is received, processes the response.

        3. Processing Broadcast Messages:
            - Checks if the response starts with "message ".
            - Attempts to parse the broadcast message using `self.response_get_broadcast_message(response)`.
            - If a valid broadcast message is found, tries to convert the message to JSON using `self.message_get_json(broadcast_message[1])`.
            - Checks if the JSON message's recipient matches the `self.starting_timestamp`.
            - If the message is `HAMSTER_OK`, sets `accepted` to True and breaks out of the loop.
            - If the message is `HAMSTER_KO`, sets `accepted` to False and breaks out of the loop.
            - Handles any exceptions during message parsing and logs debug messages.
            - Adds the broadcast message to `self.pending_broadcast` if it is not processed.

        4. Returning the Result:
            - Returns the value of `accepted`, indicating whether the cannibalism request was accepted or not.
        """
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
        """
        This function handles the cannibalism process for the current entity (e.g., a virtual hamster) in a client-server 
        interaction. The steps involved are as follows:

        1. Initialization:
            - Records the starting timestamp in self.cannibal_parent.
            - Sends a "Fork" command to the server to initialize a new search process.

        2. Server Response Handling:
            - Checks the server's response to the "Fork" command.
            - If the response is "ko", logs a debug message indicating the server's refusal and exits.
            - If the response is "ok", logs a debug message confirming the server's acceptance and proceeds.

        3. Adding a New Hamster:
            - Calls the add_hamster() method to add a new hamster.

        4. Finding a Child Hamster:
            - Enters a loop to find a child hamster until one is found.
            - Uses canniablism_find_new_hamster_from_pending_broadcast() to search for a hamster in pending broadcasts.
            - If no hamster is found, calls cannibalism_fetch_new_hamster_id() to obtain a new hamster ID.
            - Sends a broadcast message with the found hamster's ID.
            - Checks if the child hamster accepts the "cannibalism" via cannibalism_accepted().
            - If accepted, exits the loop; otherwise, continues searching.

        5. Interacting with the Server to Find Food:
            - Enters an infinite loop to look around and try to find food.
            - Sends a "Look" command to the server to get an overview of the environment.
            - Checks the server's response and converts it to a vision array.
            - Analyzes the first case in the vision to count the number of food items present.
            - If food is present, sends "Take food" commands to pick up the food.
            - If no food is found after several attempts (more than 2), exits the loop.

        6. Exception Handling:
            - Captures any exceptions raised during the process, logs an error message, and exits.
        """
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
                return

    def walk_take_object(self, items: list[str]):
        """
        Takes the specified items while walking.

        Args:
            items (list[str]): A list of items to take.
        """
        for item in items:
            if len(item) == 0:
                continue
            if item == "player":
                continue
            self.client.send(f"Take {item}\n")
            response = self.response_get_last_command()
            if response == "ko":
                self.debug(f"Server did not accept take {item}", COLOR_CYAN)
            elif response == "ok":
                self.debug(f"Took {item}", COLOR_CYAN)
            else:
                self.debug(f"Server responded with unknown message: {response}", COLOR_CYAN)
    
    def walk_forward(self):
        """
        Moves the hamster forward.

        Sends the "Forward" command to the server and checks the response.
        If the response is "ko", it prints a debug message indicating that the server did not accept the forward command.
        If the response is "ok", it prints a debug message indicating that the hamster has moved forward.
        If the response is neither "ko" nor "ok", it prints a debug message indicating that the server responded with an unknown message.

        """
        self.client.send("Forward\n")
        response = self.response_get_last_command()
        if response == "ko":
            self.debug("Server did not accept forward", COLOR_YELLOW)
        elif response == "ok":
            self.debug("Moved forward", COLOR_YELLOW)
        else:
            self.debug(f"Server responded with unknown message: {response}", COLOR_YELLOW)

    def walk_rotate_right(self):
        """
        Rotates the hamster to the right.

        Sends a "Right" command to the server and checks the response.
        If the response is "ko", it prints a debug message indicating that the server did not accept the right command.
        If the response is "ok", it prints a debug message indicating that the hamster has rotated right.
        If the response is neither "ko" nor "ok", it prints a debug message indicating that the server responded with an unknown message.

        """
        self.client.send(f"Right\n")
        response = self.response_get_last_command()
        if response == "ko":
            self.debug("Server did not accept right", COLOR_YELLOW)
        elif response == "ok":
            self.debug("Rotated right", COLOR_YELLOW)
        else:
            self.debug(f"Server responded with unknown message: {response}", COLOR_YELLOW)
    
    def walk_rotate_left(self):
        """
        Rotates the hamster to the left.

        Sends a "Left" command to the server and checks the response.
        If the response is "ko", it prints a debug message indicating that the server did not accept the left command.
        If the response is "ok", it prints a debug message indicating that the hamster has rotated left.
        If the response is neither "ko" nor "ok", it prints a debug message indicating that the server responded with an unknown message.

        """
        self.client.send(f"Left\n")
        response = self.response_get_last_command()
        if response == "ko":
            self.debug("Server did not accept left", COLOR_YELLOW)
        elif response == "ok":
            self.debug("Rotated left", COLOR_YELLOW)
        else:
            self.debug(f"Server responded with unknown message: {response}", COLOR_YELLOW)

    def walk(self):
        """
        Walks the hamster in the game world.

        This method performs a series of actions to move the hamster in the game world.
        It sends a "Look" command to the server, retrieves the response, and analyzes the vision.
        Based on the vision, it takes objects from certain cases, rotates left or right, and moves forward.
        """
        try:
            self.client.send("Look\n")
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
            self.walk_take_object(first_case_list)
            self.walk_forward()
            third_case = vision[2].strip()
            third_case_list = third_case.split(" ")
            if not third_case_list:
                raise Exception("Invalid third element in vision")
            self.debug(f"Third case: {third_case_list}", COLOR_BLUE)
            self.walk_take_object(third_case_list)
            second_case = vision[1].strip()
            second_case_list = second_case.split(" ")
            second_case_list = [item for item in second_case_list if item != "player"]
            fourth_case = vision[3].strip()
            fourth_case_list = fourth_case.split(" ")
            fourth_case_list = [item for item in fourth_case_list if item != "player"]
            if not second_case_list:
                raise Exception("Invalid second element in vision")
            self.debug(f"Second case: {second_case_list}", COLOR_BLUE)
            if not fourth_case_list:
                raise Exception("Invalid fourth element in vision")
            self.debug(f"Fourth case: {fourth_case_list}", COLOR_BLUE)
            if len(second_case_list) > len(fourth_case_list):
                self.walk_rotate_left()
            else:
                self.walk_rotate_right()
            self.walk_forward()
            if len(second_case_list) > len(fourth_case_list):
                self.walk_take_object(second_case_list)
            else:
                self.walk_take_object(fourth_case_list)
            self.walk_forward()
        except Exception as e:
            self.error(f"Error walking: {e}")
    
    def family_gathering(self):
        if self.direction_called_by_mother == 0:
            self.debug("I arrived to the mother", COLOR_GREEN)
            self.send_broadcast(f"{self.create_broadcast_message(HAMSTER_COMMING, self.cannibal_parent)}")
            return
        possible_moves = [
            [self.walk_forward()]
            [self.walk_forward(), self.walk_rotate_left(), self.walk_forward()],
            [self.walk_rotate_left(), self.walk_forward()],
            [self.walk_rotate_left(), self.walk_forward(), self.walk_rotate_left(), self.walk_forward()],
            [self.walk_rotate_right(), self.walk_rotate_right(), self.walk_forward()],
            [self.walk_rotate_right(), self.walk_forward(), self.walk_rotate_right(), self.walk_forward()],
            [self.walk_rotate_right(), self.walk_forward()],
            [self.walk_forward(), self.walk_rotate_right(), self.walk_forward()]
        ]
        for move in possible_moves[self.direction_called_by_mother]:
            move()
        self.send_broadcast(f"{self.create_broadcast_message(HAMSTER_COMMING, self.cannibal_parent)}")

    def run(self):
        """
        Run the hamster's main loop.

        This method is responsible for running the main loop of the hamster.
        It updates the inventory, manages broadcasts, checks for synchronization with other hamsters,
        and performs actions based on the hamster's state and inventory.

        Raises:
            Exception: If an error occurs in the main loop.

        """
        self.debug(f"Hamster {self.name} is running")
        self.init_hamster()

        while not self.sync_with_other_hamsters and not self.dead:
            try:
                for _ in range(10):
                    self.update_inventory()
                self.manage_broadcast()
            except Exception as e:
                self.debug(f"An error occurred in the main loop: {e}")

        self.debug(f"Hamster {self.name} is now synchronized! Am I ? { self.cannibal_parent > 0 and self.cannibal_parent != self.starting_timestamp } ; ID: { self.starting_timestamp }", COLOR_GREEN)

        if self.mother:
            self.error("I'm the mother")

        while not self.dead:
            try:
                self.manage_broadcast()
                if self.cannibal_parent > 0 and self.cannibal_parent != self.starting_timestamp:
                    # self.debug(f"Parent cannibal: {self.cannibal_parent}")
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
                    if self.mother:
                        self.debug("I'm the mother", COLOR_GREEN)
                        self.send_broadcast(f"{self.create_broadcast_message(HAMSTER_CALL_FAMILY, 0)}")
                    else:
                        if self.called_by_mother:
                            self.debug("Mother called me", COLOR_GREEN)
                            self.family_gathering()
                        else:
                            self.walk()
                self.manage_broadcast()
            except Exception as e:
                self.error(f"An error occurred in the main loop: {e}")

    def encrypt_message(self, message: str) -> str:
        """
        Encrypts a given message using the encrypting key.

        Args:
            message (str): The message to be encrypted.

        Returns:
            str: The encrypted message.
        """
        encrypted_message = ""
        key_index = 0
        for char in message:
            if char.isalpha():
                key_char = self.encrypting_key[key_index % len(self.encrypting_key)]
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
        """
        Decrypts a message using the encrypting key.

        Args:
            message (str): The message to be decrypted.

        Returns:
            str: The decrypted message.
        """
        decrypted_message = ""
        key_index = 0
        for char in message:
            if char.isalpha():
                key_char = self.encrypting_key[key_index % len(self.encrypting_key)]
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
        """
        Prints a debug message with a timestamp and the hamster's ID.

        Args:
            string (str): The debug message to be printed.
            color (str, optional): The color code to be applied to the debug message. Defaults to COLOR_RESET.
        """
        now = datetime.now()
        timestamp = now.strftime('%H:%M:%S') + f".{now.microsecond // 10:05d}"
        id_formate = f"{self.ID:03d}"
        print(f"{color}[{timestamp}] Hamster {id_formate}: {string}{COLOR_RESET}")

    def error(self, string: str):
        """
        Prints an error message with a timestamp and the hamster's ID.

        Args:
            string (str): The error message to be printed.
        """
        now = datetime.now()
        timestamp = now.strftime('%H:%M:%S') + f".{now.microsecond // 10:05d}"
        id_formate = f"{self.ID:03d}"
        print(f"{COLOR_RED}[{timestamp}] Hamster {id_formate}: {string}{COLOR_RESET}")
