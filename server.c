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
#include <time.h>

int main( int argc, char** argv )
{
    int i,j = 0;

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

    //printf("dir: %s\n", dir);
    int s1 = 0;
    int c1 = 0;
    int optval = 1;
    char ip[15] = "127.0.0.1";

    struct sockaddr_in address;
    struct sockaddr_storage otherAddress;
    socklen_t otherSize = sizeof(otherAddress);

    s1 = socket(AF_INET, SOCK_STREAM, 0);

    setsockopt(s1, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));
    
    memset(&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_port = htons(port);
    address.sin_addr.s_addr = INADDR_ANY;
    bind(s1, (struct sockaddr*)&address, sizeof(address));

    listen(s1, 1);
    
    c1 = accept(s1, (struct sockaddr*) &otherAddress, &otherSize);
    
    char req[4];
    char path[100];
    char http[10];
    char reqBuffer[200];
    char fBuffer[1024];
    struct stat* buf;
printf("got here1\n");
    for(i = 0 ; i < 99 ; ++i)
        path[i] = ' ';
    path[100] = '\0';

    i = 0;

printf("got here2\n");
    recv(c1, reqBuffer, 200, 0);
    
    sscanf(reqBuffer, "%s %s %s", req, path, http);

    while(path[i] != ' ')
        ++i;
printf("got here3\n");
    int pLen = i;
    i = 0;
    int getOrHead = 0;

    if(strncmp(req, "GET", 3) == 0)
        getOrHead = 1;
    else if(strncmp(req, "HEAD", 4) == 0)
        getOrHead = 2;

    
    printf("req: %s\npath: %s\nhttp: %s\n",req,path,http);

    if(getOrHead == 1 || getOrHead == 2 )
        {
            printf("got here4\n");
            if(path[pLen] == '/')
                {
                    printf("got here5\n");
                    strcat(path, "index.html");
                    pLen += 10;
                }
            if(path[0] == '/')
            {
                printf("got here6\n");
                for(i = 1 ; i < 100 ; ++i)
                    {
                        
                        path[i-1] = path[i];
                        --pLen;
                    }
                }
printf("got here7 path: %s\n", path);
            if(getOrHead == 1)
                {
                    FILE* file = fopen(path, "rb");
                    if(file != NULL)
                    {
                        fstat(path, buf);    
                        send(c1, "HTTP/1.0 200 OK\n", 17, 0);
                        send(c1, "Content-Length: fs.size
                        
                        
                        
                        while(fread(fBuffer, sizeof(char), 1024, file) != 0);
                            send(c1, fBuffer, 1025, 0);
                    }
                }
        }
}