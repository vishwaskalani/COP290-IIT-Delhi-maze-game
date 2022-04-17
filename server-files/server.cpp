// Server side C/C++ program to demonstrate Socket
// programming
#include "server.h"

#define PORT 8080

int server_fd, new_socket, valread;
struct sockaddr_in address;
int opt = 1;
int addrlen = sizeof(address);
char buffer[30] = { 0 };
char* hello = "Hello from server";

void serversetup(){
	// Creating socket file descriptor
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0))
		== 0) {
		perror("socket failed");
		exit(EXIT_FAILURE);
	}

	// Forcefully attaching socket to the port 8080
	if (setsockopt(server_fd, SOL_SOCKET,
				SO_REUSEADDR | SO_REUSEPORT, &opt,
				sizeof(opt))) {
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(PORT);

	// Forcefully attaching socket to the port 8080
	if (bind(server_fd, (struct sockaddr*)&address,
			sizeof(address))
		< 0) {
		perror("bind failed");
		exit(EXIT_FAILURE);
	}
	if (listen(server_fd, 3) < 0) {
		perror("listen");
		exit(EXIT_FAILURE);
	}
	if ((new_socket
		= accept(server_fd, (struct sockaddr*)&address,
				(socklen_t*)&addrlen))
		< 0) {
		perror("accept");
		exit(EXIT_FAILURE);
	}

}

// Server side C/C++ program to demonstrate Socket
// programming

void serversendmessage(char* message) {
	send(new_socket, message, strlen(message), 0);
}

char* serverreadbuffer(){
	valread = read(new_socket, buffer, 30);
	return buffer;
}

// int main(int argc, char const *argv[])
// {
// 	serversetup();
// 	serversendmessage("Hello");
// 	serverreadbuffer();
// 	return 0;
// }
