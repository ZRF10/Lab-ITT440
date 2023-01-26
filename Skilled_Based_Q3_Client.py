import socket

def main():
    
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    
    client_socket.connect(('192.168.56.102', 8080))
    
    quote = client_socket.recv(1024).decode()
    print("Received quote:", quote)
    
    client_socket.close()

if __name__ == '__main__':
    main()
