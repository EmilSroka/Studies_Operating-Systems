#include <sys/msg.h>
#include <sys/sem.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>

struct msg{
    pid_t pid;
    char action;
};

int main(void){
    struct sembuf buf;
    int semid, msgid;
    struct msg msg;

    msg.pid = getpid();

    semid = semget(434590, 1, 0);
    if(semid == -1){
        perror("Can't get semaphore");
 		exit(1);
    }

    msgid = msgget(4345910, 0);
    if(msgid  == -1){
        perror("Can't get message queue");
 		exit(1);
    }

    /* student came */

    buf.sem_num = 0;
    buf.sem_op = 1;
	buf.sem_flg = 0;
    if (semop(semid, &buf, 1) == -1){
 		perror("Can't increment semaphore");
		exit(1);
	}

    msg.action = 'c';

    if(msgsnd(msgid, &msg, sizeof(msg), 0) == -1){
        perror("Can't send message");
        exit(1);
    }

    
    /* student ate */

    while ( semctl(semid, 0, GETVAL) < 1){ 
        sleep(0);
    }

    msg.action = 'e';

    if(msgsnd(msgid, &msg, sizeof(msg), 0) == -1){
        perror("Can't send message");
        exit(1);
    }

    sleep(0);

    /* student left */

    buf.sem_op = -1;
    if (semop(semid, &buf, 1) == -1){
 		perror("Can't decrement semaphore");
		exit(1);
	}

    msg.action = 'l';

    if(msgsnd(msgid, &msg, sizeof(msg), 0) == -1){
        perror("Can't send message");
        exit(1);
    }

    return 0;
}