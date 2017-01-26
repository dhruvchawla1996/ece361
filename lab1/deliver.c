#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>


int main(int argc, char const *argv[]) {
    if (argc < 3) exit(1);

    //socket descriptor
    int sockfd;

    int serv_port = atoi(argv[2]);
    struct sockaddr_in serv_addr;
    socklen_t serv_addr_size;
    char buf[256];

    struct addrinfo hints;
    struct addrinfo *serverinfo;//will point to the results

    //making sure that the structs are empty
    memset(&hints, 0 , sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_DGRAM;


    int status;

    status = getaddrinfo(argv[1], argv[2], &hints, &serverinfo );

    bzero(buf, 256);

    serv_addr_size = sizeof(serv_addr);

    sockfd = socket(serverinfo->ai_family, serverinfo->ai_socktype, serverinfo->ai_protocol);
    //sockfd = socket(PF_INET, SOCK_DGRAM, 0);

    //serv_addr.sin_family = AF_INET;
    //serv_addr.sin_port = htons(serv_port);
    //serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    //memset(serv_addr.sin_zero, '\0', sizeof(serv_addr.sin_zero));

    fgets(buf, 256, stdin);

    char file_name[256];

    int i;

    if(buf[0]=='f'&&buf[1]=='t'&&buf[2]=='p'&&buf[3]==' ')
    {

      for( i=4; i<strlen(buf); i++)
    {
          file_name[i-4] = buf[i];
    }

      file_name[i-5] ='\0';

    }
    else
        exit(1);

    if(access(file_name, F_OK) == -1)
    {
        exit(1);
    }

    int numbytes;


    if((numbytes = sendto(sockfd, "ftp", 256, 0, serverinfo->ai_addr, serverinfo->ai_addrlen)) == -1){
        printf("talker: sendto\n");
        exit(1);
    };
    //sendto(sockfd, buf, 256, 0, (struct sockaddr *) &serv_addr, serv_addr_size);



    recvfrom(sockfd, buf, 256, 0, (struct sockaddr *) &serv_addr, &serv_addr_size);

    if(strcmp(buf,"yes") == 0 )
    printf("A file transfer can start\n");

    freeaddrinfo(serverinfo);



    close(sockfd);
    return 0;
}
