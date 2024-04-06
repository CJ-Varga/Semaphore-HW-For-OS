Created 4/5/2024 by CJ Varga

Consumer and Producer exmaple program for Operating Systems class.
consumer.c and producer.c are ran at the same time using threads.
Memory map is used to create and access shared memory for the two
files, allowing the production and consumption of data in shared
memory. A semaphore is employed to keep critical functions mutually
exclusive, so no critical section related errors are made.
