#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>

int main(void)
{
    int     pfd[2];
    pid_t   pid;
    char    string[] = "Test";
    char    buf[10];

    if(pipe(pfd) == -1){
        printf("Failed to create pipe\n");
        exit(EXIT_FAILURE);
    }
    pid = fork();

    if(pid == 0) {
        close(pfd[1]);
        close(STDIN_FILENO);              
        dup2(pfd[0], STDIN_FILENO);
        read(STDIN_FILENO, buf, sizeof(buf));
        printf("Result: %s\n", buf);
        close(pfd[0]);
    } else {
        close(pfd[0]);
        write(pfd[1], string, (strlen(string)+1)); 
        close(pfd[1]);       
    }

    return 0;
}