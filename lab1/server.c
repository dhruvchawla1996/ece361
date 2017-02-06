#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc, char const *argv[])
{
	if (argc < 2) exit(1);

	int sockfd;	// listen on socket sockfd
	int port = atoi(argv[1]);	// port to listen on
	struct sockaddr_in serv_addr, cli_addr; // structs to store server and client address info
	socklen_t clilen; // length of client info
	char buf[256];	// buffer to store client's message

	bzero(buf, 256);

	// open socket (DGRAM)
	sockfd = socket(PF_INET, SOCK_DGRAM, 0);
	if (sockfd < 0) exit(1);

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port);
	serv_addr.sin_addr.s_addr = INADDR_ANY;	// don't need to bind socket to specific IP
	memset(serv_addr.sin_zero, '\0', sizeof(serv_addr.sin_zero));

	// bind to socket
	bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr));

	clilen = sizeof(cli_addr);

	// receive from the client and store info in cli_addr for sending purposes
	if (recvfrom(sockfd, buf, 256, 0, (struct sockaddr *) &cli_addr, &clilen)==-1) {
		printf("Connection lost\n");
		exit(1);
	}

    //printf("%s", &buf);

	// send message to client based on message recevied
	if (strcmp(buf, "ftp") == 0) {
		sendto(sockfd, "yes", strlen("yes"), 0, (struct sockaddr *) &cli_addr, sizeof(serv_addr));
                printf("Connection established\n");
	} else {
		sendto(sockfd, "no", strlen("no"), 0, (struct sockaddr *) &cli_addr, sizeof(serv_addr));
                printf("Connection not established\n");
	}

	// close Connection
	close(sockfd);
	return 0;
}

