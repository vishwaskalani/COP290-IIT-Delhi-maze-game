#include "client.h"

#define PORT 8080

int sock = 0, valread;
struct sockaddr_in serv_addr;
char* hello = "Hello from client";
char buffer[30] = { 0 };

void clientsetup(){

	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		printf("\n Socket creation error \n");
	}

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);

	// Convert IPv4 and IPv6 addresses from text to binary
	// form
	if (inet_pton(AF_INET, "192.168.206.7", &serv_addr.sin_addr)
		<= 0) {
		printf(
			"\nInvalid address/ Address not supported \n");
	}

	if (connect(sock, (struct sockaddr*)&serv_addr,
				sizeof(serv_addr))
		< 0) {
		printf("\nConnection Failed \n");
	}
}

void clientsendmessage(char* message){
	send(sock, message, strlen(message), 0);
}

char* clientreadbuffer(){
	valread = read(sock, buffer, 30);
	return buffer;
}




