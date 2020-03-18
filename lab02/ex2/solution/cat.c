#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include "all.h"
#include <sys/stat.h>
#include <fcntl.h>

#define BUFFSIZE 512

int main(int argc, char *argv[]){
    char buff [BUFFSIZE];
    int n, errnoCopy, fd;

    if(argc == 1){
        do {
            if( (n = readToNL(STDIN_FILENO, buff, BUFFSIZE)) > 0) {
                write(STDOUT_FILENO, buff, n);
                write(STDOUT_FILENO, "\n", 1);
            }
        } while (n > 0);

        if(n == 0){
            exit(EXIT_SUCCESS);
        } else if(n == -1){
            errnoCopy = errno;
            perror("");
            exit(EXIT_FAILURE);
        }
    }

    if(argc > 1){
        for(int i=1; i < argc; i++){
            
            if( (fd = open(argv[i], O_RDONLY)) == -1){
                errnoCopy = errno;
                perror("");
                continue;
            }

            do {
                if( (n = readall(fd, buff, sizeof(buff))) > 0){
                    if(writeall(STDOUT_FILENO, buff, n) == -1){
                        errnoCopy = errno;
                        perror("");
                        exit(EXIT_FAILURE);
                    }
                }
            } while (n > 0);

            if(n == -1){
                errnoCopy = errno;
                perror("");
                exit(EXIT_FAILURE);
            }

            writeall(STDOUT_FILENO,"\n",1);
        }
    }
    return 0;
}