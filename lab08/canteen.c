#include <sys/msg.h>
#include <sys/sem.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <fcntl.h>

struct msg{
    pid_t pid;
    char action;
};

int main(void){
    struct sembuf buf;
    int semid, msgid;
    struct msg msg;

    semid = semget(434590, 1, IPC_CREAT | IPC_EXCL | S_IRWXU | S_IRWXG | S_IROTH | S_IWOTH);
    if(semid == -1){
        perror("Can't create semaphore");
 		exit(1);
    }

    if (semctl(semid, 0, SETVAL, 0) == -1){
 		perror("Can't initialize semaphore");
		exit(1);
	}

    msgid = msgget(4345910, IPC_CREAT | IPC_EXCL | S_IRWXU | S_IRWXG | S_IROTH | S_IWOTH);
    if(msgid  == -1){
        perror("Can't create message queue");
 		exit(1);
    }

    buf.sem_num = 0;
    buf.sem_op = -1;
	buf.sem_flg = 0;
    if (semop(semid, &buf, 1) == -1){
 		perror("Can't increment semaphore");
		exit(1);
	}

    do{
        if(msgrcv(msgid, &msg, sizeof(msg), 0, 0) == -1){
            perror("Message receiving error");
 		    exit(1);
        }

        //printf("\n\n%d\n\n", semctl(semid, 0, GETVAL));

        switch(msg.action){
            case 'c':
                printf("Student %d: Student came\n", (int)msg.pid);
            break;
            case 'e':
                printf("Student %d: Student ate\n", (int)msg.pid);
            break;
            case 'l':
                printf("Student %d: Student left\n", (int)msg.pid);
            break;
            default:
                printf("Student %d: Unknown action\n", (int)msg.pid);
                exit(1);
        }
    } while(msg.action != 'x');

    msgctl(msgid, IPC_RMID, NULL); 
    semctl(semid, 0, IPC_RMID, NULL); 
    return 0;
}