Created 4/5/2024 by CJ Varga

Consumer and Producer exmaple program for Operating Systems class.
consumer.c and producer.c are ran at the same time using threads.
POSIX shared memory is used to create and access shared memory for the two
files, allowing the production and consumption of data in shared
memory. A POSIX semaphore is employed to keep critical functions mutually
exclusive, so no critical section related errors are made.
sleep() is used through the program frequently to make the output easier
to read as well as force situations to verify that the semaphore is
preventing overlapping critical sections.
