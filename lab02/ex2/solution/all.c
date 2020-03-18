#include <errno.h>
//#include <stdio.h>
#include <unistd.h>
#include "all.h"

ssize_t writeall(int fd, const void *buf, size_t nbyte)
{
	ssize_t nwritten = 0, n;
 
	do {
		if ((n = write(fd, &((const char *)buf)[nwritten], nbyte - nwritten)) == -1) {
			if (errno == EINTR)
				continue;
			else
				return -1;
		}
		nwritten += n;
	} while (nwritten < nbyte);
	return nwritten;
}

ssize_t readall(int fd, const void *buf, size_t nbyte)
{
    ssize_t nread = 0, n;

    do {
		if ((n = read(fd, &((char *)buf)[nread], nbyte - nread)) <= 0) {
			if (errno == EINTR && n == -1)
				continue;
            else if (n == 0){
				if(nread < 2){
					return 0;
				} else {
					return nread;
				}
			} else
				return -1;
		}
		nread += n;
	} while (nread < nbyte);

	return nread;
}

ssize_t readToNL(int fd, const void *buf, size_t nbyte)
{
    ssize_t nread = 0, n;

    do {
		if ((n = read(fd, &((char *)buf)[nread], 1)) <= 0) {
			if (errno == EINTR && n == -1)
				continue;
            else if (n == 0)
                return 0;
			else
				return -1;
		}
		if(((char *)buf)[nread] == '\n' || ((char *)buf)[nread] == '\r'){
			break;
		}
		nread += n;
	} while (nread < nbyte);

	return nread;
}