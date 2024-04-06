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
#include <sys/shm.h>

//SNAME = Semaphore Name 
#define SNAME "/mySemaphore"
//SHNAME = SHared (data) Name
#define SHNAME "/shared"

int main(){

    int repeats=0;
    const int SIZE = 10;
    void *num;
    char x;
    int counter = 0;

    shm_unlink(SHNAME);
    sem_unlink(SNAME);
    //declare semaphore initialized at 1
    sem_t *sem = sem_open(SNAME, O_CREAT, 0644, 1);

    //declare shared memory
    int shm = shm_open(SHNAME, O_CREAT | O_RDWR, 0666);
    //expand size of shared memory
    ftruncate(shm, SIZE);
    //set pointer to beginning of shared
    void* ptr;
    ptr = mmap(0, SIZE, PROT_WRITE | PROT_READ, MAP_SHARED, shm, 0);

    do{
        
    while (*(char*)ptr != 0){
        printf("producer waiting...\n");
        sleep(1);//waiting until next memory location is empty
    }
    //call wait to enter critical section
    sem_wait(sem);
    printf("Producer entering critical section\n");

    //critical section
    sleep(2);
    x = (char)((rand()%24)+'a');
    int y = counter;
    //printf(y + "\n");
    num = &x;
    sprintf(ptr, "%c", x);
    printf("The Producer added %c", x);
    printf(" to slot %d", y);
    printf("\n");
    ptr += (sizeof(char));
    counter += 1;
    if (counter > SIZE){
        counter = 0;
        ptr = mmap(0, SIZE, PROT_WRITE | PROT_READ, MAP_SHARED, shm, 0);
    }
    

    //signal that critical section has been exited
    printf("Producer exiting critical section\n");
    sem_post(sem);
    sleep(1);


    repeats+=1;
    }while(repeats<15);

    sem_unlink(SNAME);
}
