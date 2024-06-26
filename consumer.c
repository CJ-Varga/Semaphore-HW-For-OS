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
#include <string.h>
#include <sys/shm.h>

//SNAME = Semaphore Name 
#define SNAME "/mySemaphore"
//SHNAME = SHared (data) Name
#define SHNAME "/shared"

int main(){
    int repeats=0;
    const int SIZE = 10;
    int x = 0;
    int *num = &x;
    int counter = 0;

    //wait for semaphore to be created
    sleep(2);

    //grab reference to same semaphore as consumer
    sem_t *sem = sem_open(SNAME, O_CREAT);

    //declare shared memory
    int shm = shm_open(SHNAME, O_CREAT | O_RDWR, 0666);
    //expand size of shared memory
    truncate(SHNAME, SIZE);
    //set pointer to beginning of shared
    void* ptr = mmap(0, SIZE, PROT_WRITE | PROT_READ, MAP_SHARED, shm, 0);

    do{
    while (*(char*)ptr == 0){
        //printf("Consumer is waiting...\n");
            //waiting until next memory location is empty
    }

    //call wait to enter critical section
    sem_wait(sem);
    printf("Consumer entering critical section\n");

    //critical section
    int y = counter;
    printf("The consumer used up ");
    printf((char*)ptr);
    printf(" from slot %d", y);
    printf("\n");
    //set the table data back to 0
    sprintf(ptr, "%c", 0);
    ptr += (sizeof(char));
    counter += 1;
    if (counter > SIZE){
        counter = 0;
        ptr = mmap(0, SIZE, PROT_WRITE | PROT_READ, MAP_SHARED, shm, 0);
    }
    

    //signal that critical section has been exited
    printf("Consumer exiting critical section\n");
    sem_post(sem);

    sleep(1);
    repeats+=1;
    }while(repeats<15);

    //release the shared data
    shm_unlink(SHNAME);
    sem_unlink(SNAME);
}
