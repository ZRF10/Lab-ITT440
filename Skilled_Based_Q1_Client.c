#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>

	int main() {
		int client_socket, rand_num;
		struct sockaddr_in server;

		// Create socket
		client_socket = socket(AF_INET, SOCK_STREAM, 0);
		if (client_socket == -1) {
			printf("Failed Create Socket");
		}
		puts("Socket created successfully");

		// Forming the sockaddr_in structure
		server.sin_family = AF_INET;
		server.sin_addr.s_addr = inet_addr("192.168.56.102");
		server.sin_port = htons(8080);

		// Connect to server
		if (connect(client_socket, (struct sockaddr *) &server, sizeof(server)) < 0) {
			perror("ERROR: Connection Failed");
			return 1;
		}
		puts("Connected to server successfully");

		// Obtain random number from server
		recv(client_socket, &rand_num, sizeof(int), 0);
		printf("Random number obtained from server: %d\n", rand_num);

		// Close the socket
		close(client_socket);
		puts("Connection has been closed");

		return 0;
	}