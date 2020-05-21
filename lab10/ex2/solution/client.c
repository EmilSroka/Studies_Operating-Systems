#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <signal.h>
#include <sys/types.h>

#define PORT 30116 // the port client will be connecting to 

#define MAXDATASIZE 100 // max number of bytes we can get at once 

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
	int sockfd, numbytes;  
	char buf[MAXDATASIZE];
	struct hostent *he;
	struct sockaddr_in their_addr; // connector's address information 
	pid_t pid;

	if (argc != 2) {
	    fprintf(stderr,"usage: client hostname\n");
	    exit(1);
	}

	if ((he=gethostbyname(argv[1])) == NULL) {  // get the host info 
		printf("gethostbyname: %s\n", hstrerror(h_errno));
	    exit(1);
	}

	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
	    perror("socket");
	    exit(1);
	}

	their_addr.sin_family = AF_INET;    // host byte order 
	their_addr.sin_port = htons(PORT);  // short, network byte order 
	their_addr.sin_addr = *((struct in_addr *)he->h_addr);
	memset(their_addr.sin_zero, '\0', sizeof their_addr.sin_zero);

	if (connect(sockfd, (struct sockaddr *)&their_addr, sizeof their_addr) == -1) {
	    perror("connect");
	    exit(1);
	}

	pid = fork();

	// exit(-69);

	if(pid == -1){
		perror("fork");
	} else if(pid == 0){
		int numbytes;
		char buf[MAXDATASIZE] = " ";

		if ((numbytes=recv(sockfd, buf, MAXDATASIZE-1, 0)) == -1) {
			perror("recv");
			exit(1);
		}
		while(strcmp(buf, "")){
			printf("Server: %s\n", buf);

			if ((numbytes=recv(sockfd, buf, MAXDATASIZE-1, 0)) == -1) {
				perror("recv");
				exit(1);
			}

			buf[numbytes] = '\0';
		}
	} else {
		char buf[MAXDATASIZE];
		int length;

		length = stdin_readall(buf,MAXDATASIZE);
		while( strcmp(buf, "") ){
			if (send(sockfd, buf, length, 0) == -1){
				perror("send");
			}

			length = stdin_readall(buf,MAXDATASIZE);
		}
		kill(pid,SIGKILL);
	}

	close(sockfd);
	return 0;
}