#include "client.h"

#define PORT 8080

int sock = 0, valread;
struct sockaddr_in serv_addr;
char* hello = "Hello from client";
char buffer[10240] = { 0 };

int setup(){

	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		printf("\n Socket creation error \n");
		return -1;
	}

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);

	// Convert IPv4 and IPv6 addresses from text to binary
	// form
	if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)
		<= 0) {
		printf(
			"\nInvalid address/ Address not supported \n");
		return -1;
	}

	if (connect(sock, (struct sockaddr*)&serv_addr,
				sizeof(serv_addr))
		< 0) {
		printf("\nConnection Failed \n");
		return -1;
	}

	return 0;}

void sendmessage(char* message){
	send(sock, message, strlen(message), 0);
}

void readbuffer(){
	valread = read(sock, buffer, 10240);
	printf("%s\n", buffer);
}


int main(int argc, char const* argv[])
{
	int bb = setup();
	sendmessage("I am ishaan");
	printf("Hello message sent\n");
	sendmessage("I am ishaan");
	printf("Hello message sent\n");
	readbuffer();
}

