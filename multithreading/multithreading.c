#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

void *run(void *something){
    int id = *(int *) something;
    usleep(abs(rand() % 1000000));
    printf("Hello from thread: %d\n", id);
    
    return NULL;
}

int main(int argc, char *argv[])
{
    srand(time(NULL));
    pthread_t thread;
    pthread_t thread2;

    int id = 1;
    int second_id = 2;
    pthread_create(&thread, NULL, &run, (void *) &id);
    pthread_create(&thread2, NULL, &run, (void *) &second_id);
  
    pthread_join(thread, NULL);
    pthread_join(thread2, NULL);
    return 0;
}