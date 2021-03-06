#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
// ----------------------------------------------------------

void *PrintHello(void *arg);
// ----------------------------------------------------------

int main(int argc, char *argv[]){
     pthread_t threads [10];
     int arg[10];

     for(int i=0; i<10; i++){
          arg[i] = i;
          int rc = pthread_create(&threads[i], NULL, PrintHello, (void *)&arg[i]);
          if (rc){
               printf("Return code: %d\n", rc);
               exit(-1);
          }
     }

     for(int i=0; i<10; i++){
          pthread_join(threadsd[i], NULL);
     }
     
     printf("End of the main thread!\n");
     return 0;
}
// ----------------------------------------------------------

void *PrintHello(void *arg){
     sleep(1);
     printf("Next boring 'Hello World!' version! >> %d\n", *((int*) arg));
     return NULL;
}