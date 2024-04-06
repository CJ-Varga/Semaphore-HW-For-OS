#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/stat.h>

#define SNAME "/mySemaphore"
#define SHNAME "/shared"

int main(){
    printf("Hello");

    //declare semaphore initialized at 1
    sem_t *sem = sem_open(SNAME, O_CREAT, 0644, 1);

    //declare shared memory
    int shm = shm_open(SHNAME, O_CREAT, 0644);

    //call wait to enter critical section
    sem_wait(sem);
    printf("Producer entering critical section");

    //critical section
    sleep(2);

    //signal that critical section has been exited
    printf("Producer exiting critical section");
    sem_post(sem);
}
