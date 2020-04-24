#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]){

    int pfd[2];
    size_t nread;
    char buf[100];
    long bufSize = 0;

    pipe(pfd);
    char * str ="Ur beautiful pipe example";

    switch(fork()){
        case -1: 
            printf("Error");
            break;
        case 0:
            close(pfd[1]);
            bufSize = fpathconf(pfd[0], _PC_PIPE_BUF);
            printf("Bytes that can be written atomically to a pipe: %ld\n",bufSize);
            nread=read(pfd[0],buf, sizeof(buf) - 1);
            buf[nread] = '\0';
            (nread!=0) ?
                printf("%s (%ld bytes)\n",buf,(long)nread):
                printf("No data\n");
            close(pfd[0]);
            break;
        default:
            close(pfd[0]);
            write(pfd[1], str, strlen(str));
            close(pfd[1]);
    }
    return 0;
}