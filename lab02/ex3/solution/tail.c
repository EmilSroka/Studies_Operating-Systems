#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>

void printErrorAndClose(int errnoCopy, int fd){
	printf("\n%s\n", strerror(errnoCopy));
    close(fd);
	exit(EXIT_FAILURE);
}


void tail(char *path, int numOflines)
{
	char buff[256], c;
	int fd, readC;
	off_t where, last;
 
	fd = open(path, O_RDONLY);
	last = where = lseek(fd, 0, SEEK_END);
    do {
        where--;
        switch (pread(fd, &c, 1, where)) {
            case 1:
                if (c == '\n')
                    numOflines--;
                break;
            case -1:
                printErrorAndClose(errno, fd);
				break;
            default:
				errno = 0;
        }
    } while (where > 0 && numOflines > 0);

    if(where != 0) where++;
    lseek(fd, where, SEEK_SET);

    while(readC = read(fd, buff, 256)){
        if(readC == -1){
            printErrorAndClose(errno, fd);
        }
        write(STDOUT_FILENO, buff, readC);
    }
    write(STDOUT_FILENO, "\n", 1);
	close(fd);
	return;
}


int main(int argc, char *argv []){
    if(argc == 2){
        tail(argv[1], 5);
    }
    if(argc > 2){
        tail(argv[1], atoi(argv[2]));
    }
    return 0;
}