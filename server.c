#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <ctype.h>

int main( int argc, char **argv )
{
	if(argc != 3)
		{
			printf("Usage: ./server <port> <path to root>\n");	
			return 0;
		}

	int port = atoi(argv[1]);
	const char* dir = argv[2];
	
	if(chdir(dir) == -1)
		{
			printf("Could not change to directory: %s\n", dir);
			return 0;
		}

	int s1 = -1;
	int optval = 1;
	char ip[15] = "127.0.0.1";
	s1 = socket(AF_INET, SOCK_STREAM,0);
	
	struct sockaddr_in address;
	memset(&address, 0, sizeof(address));
	address.sin_family = AF_INET;
	address.sin_port = htons(port);
	inet_pton(AF_INET, ip, &(address.sin_addr));
	
	setsockopt(s1, SOL_SOCKET, SO_REUSEADDR, &optval , sizeof(optval));
	
	listen(s1, 1);
	struct sockaddr_storage otherAddress;
	socklen_t otherSize = sizeof(otherAddress);
	int otSoc;
	
	otSoc = accept(s1, (struct sockaddr*) &otherAddress, &otherSize);
	
	char buffer[100];
	
	recv(otSoc, buffer, 100, 0);
	
	printf("BUFFER---  : \n\n\n%s", buffer);	
}
