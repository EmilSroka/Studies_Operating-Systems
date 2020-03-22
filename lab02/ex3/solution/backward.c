#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include

void printErrorAndClose(int errnoCopy){
	printf("\n%s\n", strerror(errnoCopy));
	exit(EXIT_FAILURE);
}

void backward(char *path)
{
	char s[256], c;
	int i, fd;
	off_t where;
 
	fd = open(path, O_RDONLY);
	where = lseek(fd, 0, SEEK_END);
	i = sizeof(s) - 1;
	s[i] = '\0';
	do {
		where--;
		switch (pread(fd, &c, 1, where)) {
			case 1:
				if (c == '\n') {
					printf("%s", &s[i]);
					i = sizeof(s) - 1;
				}
				if (i <= 0) {
					errno = E2BIG;
					i = sizeof(s) - 1;
				 	write(STDERR_FILENO, "Line is too long\n", 17);
				}
				s[--i] = c;
				break;
			case -1:
				printErrorAndClose(errno);
				break;
			default:
				errno = 0;
		}
	} while (where > 0);
	printf("%s", &s[i]);
	close(fd);
	return;
}

int main(int argc, char* argv[]){
    if(argc > 1){
        backward(argv[1]);
    }
    return 0;
}