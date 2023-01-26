    #include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <unistd.h>

	int main() {
		int serverSocket, clientSocket;
		struct sockaddr_in server, client;
		int c, randNum;
		socklen_t client_len;

		// Creating socket
		serverSocket = socket(AF_INET, SOCK_STREAM, 0);
		if (serverSocket == -1) {
			printf("Failed Create Socket");
		}
		puts("Socket created successfully");

		// Forming the sockaddr_in structure
		server.sin_family = AF_INET;
		server.sin_addr.s_addr = INADDR_ANY;
		server.sin_port = htons(8080);

		// Bind
		if (bind(serverSocket, (struct sockaddr *) &server, sizeof(server)) < 0) {
			perror("Error Binding Failed. ");
			return 1;
		}
		puts("Bind Success");

		// Listen
		listen(serverSocket, 3);

		// Accept connection
		puts("Waiting for connections...");
		client_len = sizeof(struct sockaddr_in);

		while ((clientSocket = accept(serverSocket, (struct sockaddr *) &client, &client_len))) {
			puts("Connection Accepted");

			// Generate a random number from 100 to 999 
			randNum = rand() % 900 + 100;
			
			// Send random number to client
			send(clientSocket, &randNum, sizeof(int), 0);
			printf("Random number has been sent to client: %d\n", randNum);

			// Close the socket
			close(clientSocket);
			puts("Connection Closed");
		}

		if (clientSocket < 0) {
			perror("Error Accept failed");
			return 1;
		}

		return 0;
	}