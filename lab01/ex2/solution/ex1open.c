#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
 
#define BUFSIZE 1024
 
int main (int argc, char **argv) 
{
    int f1, c;
    char b[BUFSIZE], *n1;
 
    c = 10;
    n1 = argv[1];
 
    if( (f1 = open (n1, O_RDONLY)) != -1){
	
	if( read (f1, b, c) != -1){
		printf("%s: Przeczytano %d znakow z pliku %s: \"%s\"\n",
	   		argv[0], c, n1, b);
	}else{
		int errsv = errno;
		perror(strerror(errsv));
		exit(EXIT_FAILURE);		
	}

	close(f1);

    } else {
	int errsv = errno;
	perror(strerror(errsv));
	exit(EXIT_FAILURE);
    }
	
    return(0);
}
