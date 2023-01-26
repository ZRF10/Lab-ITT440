import socket

def main():
    # create a socket object
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    # get local machine name
    host = socket.gethostname()

    port = 8080

    # connection to hostname on the port.
    s.connect((host, port))

    temp_fahrenheit = input("Enter temperature in Fahrenheit: ")
    s.send(temp_fahrenheit.encode())

    # receive data from the server
    temp_celsius = s.recv(1024).decode()
    print("Temperature in Celsius: %s" % temp_celsius)

    s.close()

if __name__ == '_main_':
    main()