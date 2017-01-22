#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>

int main(int argc, char const *argv[]) {
    if (argc < 3) exit(1);

    int sockfd;
    int serv_port = atoi(argv[2]);
    struct sockaddr_in serv_addr;
    char buf[256];

    bzero(buf, 256);

    sockfd = socket(PF_INET, SOCK_DGRAM, 0);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(serv_port);
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    memset(serv_addr.sin_zero, '\0', sizeof(serv_addr.sin_zero));

    close(sockfd);
    return 0;
}
