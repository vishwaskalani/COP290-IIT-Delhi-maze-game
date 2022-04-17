#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#define PORT 8080

void clientsetup();
void clientsendmessage(char* message);
char* clientreadbuffer();

