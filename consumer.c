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

#define SNAME "/mySemaphore"

int main(){
    printf("Hello");

    //declare semaphore
    sem_t *sem = sem_open(SNAME, 0_CREAT, 0644, 1);

    //call wait to enter critical section
    //sem_wait(&sem);

    //critical section
    //sleep(4);

    //signal that critical section has been exited
}