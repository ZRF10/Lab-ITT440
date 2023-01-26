import random
import socket
import threading

# List of quotes
quotes = [
     "Wake Up - Coffe - Code - Sleep",
     "Coding is FUN - Legit T.T",
     "Keep going in Coding until you find the error is ';'",
]

def handle_client(client_socket):
    """Handles a single client's request for a quote"""
    
    client_socket.send(random.choice(quotes).encode())
    client_socket.close()

def main():
    
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    
    server_socket.bind(('192.168.56.102', 8080))
    
    server_socket.listen()

    while True:
        client_socket, client_address = server_socket.accept()

        client_thread = threading.Thread(target=handle_client, args=(client_socket,))
        client_thread.start()

if __name__ == '__main__':
    main()
