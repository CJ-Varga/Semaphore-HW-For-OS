//Producer-Consumer Homework's Producer Process
//CJ Varga
//Creatd 4/5/2024

#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

#define SNAME "/mySemaphore"
#define SHNAME "/shared"

int main(){
    const int SIZE = 255;

    //declare semaphore initialized at 1
    sem_t *sem = sem_open(SNAME, O_CREAT, 0644, 1);

    //declare shared memory
    int shm = shm_open(SHNAME, O_CREAT, 0644);
    //expand size of shared memory
    truncate(SHNAME, SIZE);
    //set pointer to beginning of shared
    void* ptr = mmap(0, SIZE, PROT_WRITE | PROT_READ, MAP_SHARED, shm, 0);


    do{
        //waiting until next memory location is empty
    } while (*(int*)ptr != 0);

    //call wait to enter critical section
    sem_wait(sem);
    printf("Producer entering critical section");

    //critical section
    printf(ptr, "%i", ((rand()%100)+1));

    //signal that critical section has been exited
    printf("Producer exiting critical section");
    sem_post(sem);
}
