#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include "packet.h"

int main(int argc, char const *argv[]) {
    if (argc < 3) {
        exit(1);
    }

    //socket descriptor
    int sockfd;

    int serv_port = atoi(argv[2]);
    struct sockaddr_in serv_addr;

    struct addrinfo hints;
    struct addrinfo *serverinfo;//will point to the results

    //making sure that the structs are empty
    memset(&hints, 0 , sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_DGRAM;

    // DNS lookup
    int status = getaddrinfo(argv[1], argv[2], &hints, &serverinfo );
    socklen_t serv_addr_size = sizeof(serv_addr);

    sockfd = socket(serverinfo->ai_family, serverinfo->ai_socktype, serverinfo->ai_protocol);

    // get user input
    char buf[256];
    bzero(buf, 256);
    fgets(buf, 256, stdin);

    char file_name[256];

    // check if file exists
    if(buf[0]=='f' && buf[1]=='t' && buf[2]=='p') {
        int i = 3;
        while (buf[i] == ' ') {
            i++;
        }

        int file_name_char = 0;
        while (buf[i] != ' ' && buf[i] != '\n') {
            file_name[file_name_char] = buf[i];

            file_name_char++;
            i++;
        }

        file_name[file_name_char] ='\0';

    } else {
        exit(1);
    }

    // Checking if the file exists.
    if(access(file_name, F_OK) == -1) {
        printf("File \"%s\" doesn't exist.\n", file_name);
        exit(1);
    }

    int numbytes;
    if((numbytes = sendto(sockfd, "ftp", strlen("ftp"), 0, serverinfo->ai_addr, serverinfo->ai_addrlen)) == -1){
        printf("talker: sendto\n");
        exit(1);
    };

    bzero(buf, 256);

    recvfrom(sockfd, buf, 256, 0, (struct sockaddr *) &serv_addr, &serv_addr_size);


    if(strcmp(buf,"yes") == 0) {
        printf("A file transfer can start\n");
    }

    freeaddrinfo(serverinfo);
    close(sockfd);

    return 0;
}
