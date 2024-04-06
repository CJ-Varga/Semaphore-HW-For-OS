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
#include <string.h>

#define SNAME "/mySemaphore"
#define SHNAME "/shared"

int main(){
    int repeats=0;
    const int SIZE = 39;
    int *num;
    int x;
    int counter;

    sem_unlink(SNAME);
    //declare semaphore initialized at 1
    sem_t *sem = sem_open(SNAME, O_CREAT, 0644, 1);

    //declare shared memory
    int shm = shm_open(SHNAME, O_CREAT, 0644);
    //expand size of shared memory
    truncate(SHNAME, SIZE);
    //set pointer to beginning of shared
    void* ptr = mmap(0, SIZE, PROT_WRITE | PROT_READ, MAP_SHARED, shm, 0);


    do{
    //do{
    //    sleep(1);//waiting until next memory location is empty
    //} while (*(int*)ptr != NULL);

    //call wait to enter critical section
    sem_wait(sem);
    printf("Producer entering critical section\n");

    //critical section
    sleep(2);
    x = ((rand()%100)+1);
    num = &x;
    //memcpy(ptr, num, sizeof(int));
    ptr += (sizeof(int));
    counter += 4;
    if (counter > SIZE){
        counter = 0;
        ptr = mmap(0, SIZE, PROT_WRITE | PROT_READ, MAP_SHARED, shm, 0);
    }
    

    //signal that critical section has been exited
    printf("Producer exiting critical section\n");
    sem_post(sem);
    sleep(1);
    repeats+=1;
    }while(repeats<5);
    shm_unlink(SHNAME);
    sem_unlink(SNAME);
}
