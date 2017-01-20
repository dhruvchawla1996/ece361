#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>

int main(int argc, char const *argv[])
{
	if (argc < 2) exit(1);

	int sockfd;	// listen on socket sockfd
	int port = atoi(argv[1]);	// port to listen on
	struct sockaddr_in serv_addr, cli_addr;
	char buf[256];	// buffer to store client's message

	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sockfd < 0) exit(1);

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port);
	serv_addr.sin_addr.s_addr = INADDR_ANY;	// don't need to bind socket to specific IP

	bind(sockfd, (struct sockaddr *) &serv_addr, sizeof serv_addr);
	listen(sockfd, 10);

	close(sockfd);
	return 0;
}