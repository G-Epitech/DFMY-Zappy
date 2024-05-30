##
## EPITECH PROJECT, 2024
## zappy
## File description:
## main
##

from classes.client import SocketClient
import getopt
import sys

EXIT_SUCCESS = 0
EXIT_FAILURE = 84

def print_usage():
    usage = """
    USAGE: ./zappy_ai -p port -n name [-h host]

    Arguments:
        -p, --port      Port number to connect to the server (required).
        -n, --name      Name of the client (required).
        -h, --host      Hostname or IP address of the server (optional, default: localhost).

    Example:
        python zappy_ai.py -p 65432 -n my_client_name -h 127.0.0.1
        python zappy_ai.py -p 65432 -n my_client_name  # Uses default host 'localhost'
    """
    print(usage)
    sys.exit(EXIT_SUCCESS)

def main(argv):
    port = 0
    name = ''
    host = '127.0.0.1'

    try:
        opts, args = getopt.getopt(argv, "p:n:h:", ["port=", "name=", "host="])
    except getopt.GetoptError:
        print_usage()

    for opt, arg in opts:
        if opt in ("-p", "--port"):
            port = int(arg)
        elif opt in ("-n", "--name"):
            name = arg
        elif opt in ("-h", "--host"):
            host = arg

    if not port or not name:
        print_usage()
    if port < 0 or port > 65535:
        print("Port must be between 0 and 65535")
        sys.exit(EXIT_FAILURE)

    print(f"Starting client with name: {name}")

    try:
        client = SocketClient(host, port)
        client.connect()
        client.send(f"Hello, Server! This is {name}")

        # Attempt to receive data in a non-blocking manner
        response = client.receive()
        if response:
            print(f"Received: {response}")
        else:
            print("No data received")

        client.close()
    except Exception as e:
        print(f"An error occurred: {str(e)}")
        sys.exit(EXIT_FAILURE)

if __name__ == "__main__":
    main(sys.argv[1:])
