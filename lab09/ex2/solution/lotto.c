#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

int main(void){
    int pid;
    
    umask(0);

    pid = fork();
    if(pid < 0){
        perror(NULL);
        exit(EXIT_FAILURE);
    }
    if(pid > 0){
        exit(EXIT_SUCCESS);
    }

    if(setsid() == -1){
        perror(NULL);
        exit(EXIT_FAILURE);
    }

    if(chdir("/tmp") == -1){
        perror(NULL);
        exit(EXIT_FAILURE);
    }

    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    while(1){
        system("shuf -i1-49 -n 6 > wyniki_lotto");
        sleep(30);
    }

    return 0;
}