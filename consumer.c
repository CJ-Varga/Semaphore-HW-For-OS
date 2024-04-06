//Producer-Consumer Homework's Consumer Process
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
#include <cstring>

#define SNAME "/mySemaphore"
#define SHNAME "/shared"

int main(){
    const int SIZE = 255;
    int x = 0;
    int *num = &x;
    int counter;

    //wait for semaphore to be created
    sleep(2);

    //grab reference to same semaphore as consumer
    sem_t *sem = sem_open("/mySemaphore", 0);

    //declare shared memory
    int shm = shm_open(SHNAME, O_CREAT, 0644);
    //expand size of shared memory
    truncate(SHNAME, SIZE);
    //set pointer to beginning of shared
    void* ptr = mmap(0, SIZE, PROT_WRITE | PROT_READ, MAP_SHARED, shm, 0);

    do{
    do{
        //waiting until next memory location is empty
    } while (*(int*)ptr == 0);

    //call wait to enter critical section
    sem_wait(sem);
    printf("Consumer entering critical section");

    //critical section
    printf("%i", (int*)ptr);
    memcpy(ptr, num, sizeof(int));
    ptr += (sizeof(int));
    counter += 4;
    if (counter > 255){
        counter = 0;
        ptr = mmap(0, SIZE, PROT_WRITE | PROT_READ, MAP_SHARED, shm, 0);
    }
    

    //signal that critical section has been exited
    printf("Consumer exiting critical section");
    sem_post(sem);
    }while(0==0);
}
