#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

#define BUFF_SIZE 100

int main(void){
    int fd1, fd2, fd3;
    char buff [100];
    fd1 = open("./test.txt", O_WRONLY);
    fd2 = open("./test.txt", O_RDONLY);
    write(fd1, "cccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc", 100);
    read(fd2, buff, 100);
    write(STDOUT_FILENO, buff, 100);

    write(STDOUT_FILENO, "\n", 1);

    fd3 = open("./test.txt", O_RDWR);
    write(fd3, "dddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddd", 100);
    read(fd2, buff, 100);
    write(STDOUT_FILENO, buff, 100);

    write(STDOUT_FILENO, "\n", 1);

    return 0;
}