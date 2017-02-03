#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc, char const *argv[])
{
    char buf[256];
    bzero(buf, 256);
    fgets(buf, 256, stdin);

    char file_name[256];

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
//        for(i = 4; i < strlen(buf); i++) {
//            file_name[i-4] = buf[i];
//        }

        file_name[file_name_char] ='\0';
    }
    printf("File name is %s, thicc boi...\n", file_name);
#if 0
	if (argc < 2) exit(1);

	int sockfd;	// listen on socket sockfd
	int port = atoi(argv[1]);	// port to listen on
	struct sockaddr_in serv_addr, cli_addr;
	socklen_t clilen;
	char buf[256];	// buffer to store client's message

	bzero(buf, 256);

	sockfd = socket(PF_INET, SOCK_DGRAM, 0);
	if (sockfd < 0) exit(1);

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port);
	serv_addr.sin_addr.s_addr = INADDR_ANY;	// don't need to bind socket to specific IP
	memset(serv_addr.sin_zero, '\0', sizeof(serv_addr.sin_zero));

	bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr));

	clilen = sizeof(cli_addr);

	recvfrom(sockfd, buf, 256, 0, (struct sockaddr *) &cli_addr, &clilen);
        
        printf("%s", &buf);
        
	if (strcmp(buf, "ftp") == 0) {
		sendto(sockfd, "yes", 256, 0, (struct sockaddr *) &cli_addr, sizeof(serv_addr));
                printf("Connection established\n");
	} else {
		sendto(sockfd, "no", 256, 0, (struct sockaddr *) &cli_addr, sizeof(serv_addr));
                printf("Connection not established\n");
	} 

	close(sockfd);
	return 0;
#endif
}
