//Producer-Consumer Homework
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


int main(){
    //wait for semaphore to be created
    sleep(2);

    //grab reference to same semaphore as consumer
    sem_t *sem = sem_open("/mySemaphore", 0);
}