// Server side C/C++ program to demonstrate Socket
// programming
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <cstring>
#include <sys/socket.h>
#include <iostream>
#include <ostream>
#include <unistd.h>
#define PORT 8080

using namespace std;

void serversetup();

string serversendmessage(char* message);

void serverreadbuffer();


