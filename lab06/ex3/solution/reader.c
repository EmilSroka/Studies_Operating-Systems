#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>

#define BUF_SIZE 100

int main(int argc, char *argv[]){
    if(argc < 2){ return -1; }

    int fd1pc[2], fd1cp[2], fd2pc[2], fd2cp[2];
    pid_t pid;

    if(pipe(fd1pc) == -1 || pipe(fd1cp) == -1 || pipe(fd2pc) == -1 || pipe(fd2cp) == -1){
        printf("Failed to create pipe");
        exit(EXIT_FAILURE);
    }

    if((pid = fork()) == -1){
        printf("Failed to create subprocess");
        exit(EXIT_FAILURE);
    }

    if(pid == 0){
        close(fd2pc[0]);
        close(fd2pc[1]);
        close(fd2cp[0]);
        close(fd2cp[1]);
        close(fd1pc[1]);
        close(fd1cp[0]);
        close(STDIN_FILENO);
        close(STDOUT_FILENO);
        dup2(fd1pc[0], STDIN_FILENO);
        dup2(fd1cp[1], STDOUT_FILENO);
        execlp("wc", "wc", "-l", NULL);
        exit(EXIT_FAILURE);
    }
    
    if((pid = fork()) == -1){
        printf("Failed to create subprocess");
        exit(EXIT_FAILURE);
    }

    if(pid == 0){
        close(fd1pc[0]);
        close(fd1pc[1]);
        close(fd1cp[0]);
        close(fd1cp[1]);
        close(fd2pc[1]);
        close(fd2cp[0]);
        close(STDIN_FILENO);
        close(STDOUT_FILENO);
        dup2(fd2pc[0], STDIN_FILENO);
        dup2(fd2cp[1], STDOUT_FILENO);
        execlp("grep", "grep", "-c", "pipe", NULL);
        exit(EXIT_FAILURE);
    }

    int fd;
    char buf[BUF_SIZE];
    int nread;
    close(fd1pc[0]);
    close(fd1cp[1]);
    close(fd2pc[0]);
    close(fd2cp[1]);
    fd = open(argv[1], O_RDONLY);
    while( (nread = read(fd, buf, sizeof(buf))) != 0){
        //printf("READ\n");

        if(nread < 0){
            perror(NULL);
            exit(EXIT_FAILURE);
        }

        if( write(fd1pc[1], buf, nread) == -1){
            perror(NULL);
            exit(EXIT_FAILURE);
        }

         if( write(fd2pc[1], buf, nread) == -1){
            perror(NULL);
            exit(EXIT_FAILURE);
        }
    }

    close(fd1pc[1]);
    close(fd2pc[1]);

    memset(buf, 0, sizeof buf);
    if( read(fd1cp[0], buf, sizeof(buf)) == -1 ){
        printf("Failed to communicate with subprocess");
        exit(EXIT_FAILURE);
    }
    printf("Number of words: %s", buf);

    memset(buf, 0, sizeof buf);
    if( read(fd2cp[0], buf, sizeof(buf)) == -1 ){
        printf("Failed to communicate with subprocess");
        exit(EXIT_FAILURE);
    }
    printf("Number of words that contain 'pipe': %s", buf);
      
    close(fd1cp[0]);
    close(fd2cp[0]);
    
    return 0;
}