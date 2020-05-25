/*
** talker.c -- a datagram "client" demo
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <signal.h>

#include <unistd.h>
       #include <fcntl.h>

#define MAXDATASIZE 100

int stdin_readall(char* dest, int MAXLEN)
{
  char c;
  int bread = 0, b;
  do
    {
      b = scanf("%c", &c);
      dest[bread] = c;
      bread++;
    }
  while((c != '\n') && (b == 1) && (bread < MAXLEN));

  dest[bread-1] = '\0';

  return bread; // strcmp(dest, "q");
}

int main(int argc, char *argv[])
{
	int sockfd;
	struct sockaddr_in their_addr; // connector's address information
	struct sockaddr_in my_addr; 
	struct hostent *he;
	int numbytes;
	socklen_t addr_len;
	pid_t pid;

	if (argc != 5) {
		fprintf(stderr,"incorrect arguments\n");
		exit(1);
	}

	if ((he=gethostbyname(argv[3])) == NULL) {  // get the host info
		perror("gethostbyname");
		exit(1);
	}

	their_addr.sin_family = AF_INET;	 // host byte order
	their_addr.sin_port = htons(atoi(argv[4])); // short, network byte order
	their_addr.sin_addr = *((struct in_addr *)he->h_addr);
	memset(their_addr.sin_zero, '\0', sizeof their_addr.sin_zero);
	addr_len = sizeof their_addr;

	my_addr.sin_family = AF_INET;		 
	my_addr.sin_port = htons(atoi(argv[2]));
	// my_addr.sin_addr.s_addr = inet_pton(AF_INET, argv[1], sizeof(argv[1])); // automatically fill with my IP
	inet_pton(AF_INET, argv[1], &my_addr.sin_addr.s_addr); 
	memset(my_addr.sin_zero, '\0', sizeof my_addr.sin_zero);

	if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
		perror("socket");
		exit(1);
	}

	if (bind(sockfd, (struct sockaddr *)&my_addr, sizeof my_addr) == -1) {
		perror("bind");
		exit(1);
	}

	pid = fork();

	if(pid == -1){
		perror("fork");
	} else if(pid == 0){
		char buf[MAXDATASIZE];
		int length;

		while(1){
			length = stdin_readall(buf,MAXDATASIZE);
			if ((numbytes = sendto(sockfd, buf, length, 0,
				(struct sockaddr *)&their_addr, sizeof(their_addr))) == -1) {
				perror("sendto");
				exit(1);
			}
		}
	} else {
		char buf[MAXDATASIZE];

		if ((numbytes = recvfrom(sockfd, buf, MAXDATASIZE-1 , 0,
			(struct sockaddr *)&their_addr, &addr_len)) == -1) {
			perror("recvfrom");
			exit(1);
		}
		while(strcmp(buf, "bye")){
			printf("%s: %s\n", inet_ntoa(their_addr.sin_addr) , buf);
			if ((numbytes = recvfrom(sockfd, buf, MAXDATASIZE-1 , 0,
				(struct sockaddr *)&their_addr, &addr_len)) == -1) {
				perror("recvfrom");
				exit(1);
			}
		}
		kill(pid,SIGKILL);
	}

	close(sockfd);
	return 0;
}