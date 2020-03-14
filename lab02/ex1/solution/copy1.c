#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
    
#define BUFSIZE 512

void handleError(int errorNumber){
    if(errorNumber == ENOENT){
        fprintf(stderr, "No such file or directory\n");
    } else if(errorNumber == EACCES){
        fprintf(stderr, "Permission denied\n");
    } else {
        fprintf(stderr,  "%s\n", strerror(errorNumber));
    }
    exit(EXIT_FAILURE); 
}
    
void copy(char *from, char *to)  /* has a bug */
{
    int errnoCopy;
    int fromfd = -1, tofd = -1;
    ssize_t nread;
    char buf[BUFSIZE];
    
    if( (fromfd = open(from, O_RDONLY)) == -1 ){
        handleError(errno);
    }

    if( (tofd = open(to, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR)) == -1){
        errnoCopy = errno;
        close(fromfd);
        handleError(errnoCopy);
    }

    while ((nread = read(fromfd, buf, sizeof(buf))) > 0){
        if(nread == -1){
            errnoCopy = errno;
            close(fromfd);
            close(tofd);
            handleError(errnoCopy);
        }

        if(write(tofd, buf, nread) == -1){
            errnoCopy = errno;
            close(fromfd);
            close(tofd);
            handleError(errnoCopy);
        }
    }
        	   
    close(fromfd);
    close(tofd);
    return;
}
    
int main(int argc, char **argv){
    if (argc != 3)
    {
        fprintf(stderr,"usage: %s from_pathname to_pathname\n", argv[0]);
        return 1;
    }
    copy(argv[1], argv[2]);
    return 0;
}