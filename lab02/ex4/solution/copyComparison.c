#include <stdio.h>
#include <sys/times.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>

static struct tms tbuf1;
static clock_t real1;
static long clock_ticks;

#define BUFSIZE 2048

void timestart(void)
{
	real1 = times(&tbuf1);
	clock_ticks = sysconf(_SC_CLK_TCK);
	return;
}

void timestop(char *msg)
{
	struct tms tbuf2;
	clock_t real2;

	real2 = times(&tbuf2);
	fprintf(stdout, "%s:\n\t\"Total (user/sys/real)\", %ld, %ld, %ld\n\t\"Child (user/sys)\", %ld, %ld\n", 
		msg,
	  	(long)((tbuf2.tms_utime + tbuf2.tms_cutime) - (tbuf1.tms_utime + tbuf1.tms_cutime)),
	  	(long)((tbuf2.tms_stime + tbuf2.tms_cstime) - (tbuf1.tms_stime + tbuf1.tms_cstime)),
		(long)(real2 - real1),
	  	(long)(tbuf2.tms_cutime - tbuf1.tms_cutime),
	  	(long)(tbuf2.tms_cstime - tbuf1.tms_cstime));
	return;
}

void copy3(char *from, char *to)
{
    FILE *stfrom, *stto;
    int c;
    
    if ((stfrom = fopen(from, "r") ) == NULL){}
    if(( stto = fopen(to, "w") ) == NULL) {}
    while ((c = getc(stfrom)) != EOF)
        putc(c, stto);
    fclose(stfrom);
    fclose(stto);
    return;
    
}

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
    
void copy2(char *from, char *to)
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
    
int main(int argc, char** argv){
    timestart();
    copy2(argv[1], argv[2]);
    timestop("copy2");
    timestart();
    copy3(argv[1], argv[2]);
    timestop("copy3");
    return 0;
}