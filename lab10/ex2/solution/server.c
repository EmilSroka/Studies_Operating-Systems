#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/types.h>

#define MYPORT 30116	// the port users will be connecting to
#define MAXDATASIZE 100 

#define BACKLOG 10	 // how many pending connections queue will hold

void sigchld_handler(int s)
{
	while(waitpid(-1, NULL, WNOHANG) > 0);
}

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

int main(void)
{
	int sockfd, new_fd;  // listen on sock_fd, new connection on new_fd
	struct sockaddr_in my_addr;	// my address information
	struct sockaddr_in their_addr; // connector's address information
	socklen_t sin_size;
	struct sigaction sa;
	int yes=1;
	pid_t pid;


	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("socket");
		exit(1);
	}

	if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
		perror("setsockopt");
		exit(1);
	}
	
	my_addr.sin_family = AF_INET;		 // host byte order
	my_addr.sin_port = htons(MYPORT);	 // short, network byte order
	my_addr.sin_addr.s_addr = INADDR_ANY; // automatically fill with my IP
	memset(my_addr.sin_zero, '\0', sizeof my_addr.sin_zero);

	if (bind(sockfd, (struct sockaddr *)&my_addr, sizeof my_addr) == -1) {
		perror("bind");
		exit(1);
	}

	if (listen(sockfd, BACKLOG) == -1) {
		perror("listen");
		exit(1);
	}

	sa.sa_handler = sigchld_handler; // reap all dead processes
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	if (sigaction(SIGCHLD, &sa, NULL) == -1) {
		perror("sigaction");
		exit(1);
	}

	sin_size = sizeof their_addr;
	if ((new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size)) == -1) {
		
	}
	printf("server: got connection from %s\n",inet_ntoa(their_addr.sin_addr));

	pid = fork();

	if(pid == -1){
		perror("fork");
	} else if(pid == 0){
		int numbytes;
		char buf[MAXDATASIZE] = " ";

		if ((numbytes=recv(new_fd, buf, MAXDATASIZE-1, 0)) == -1) {
			perror("recv");
			exit(1);
		}
		while(strcmp(buf, "")){
			printf("Client: %s\n", buf);

			if ((numbytes=recv(new_fd, buf, MAXDATASIZE-1, 0)) == -1) {
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
			if (send(new_fd, buf, length, 0) == -1){
				perror("send");
			}

			length = stdin_readall(buf,MAXDATASIZE);
		}
		kill(pid,SIGKILL);
	}

	close(new_fd);
	return 0;
}