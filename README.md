Lab materials for my Operating Systems course at University.
It has taught me a lot about processes, threads, synchronization, shared memory and all around around Linux and C practices.



2-1: Hello World program using only system calls

2-2: Copies first file from the argument into the second file from the argument

4-1: Creates a new process with fork(2) and shows the files from the current directory with execve(2)

4-2: Tests the Collatz hypothesis generating the sequence of a number in the child process

4-3: Tests the Collatz hypothesis for multiple numbers creating a child process for each one

5-1: Tests the Collatz hypothesis using shared memory. Each child process handles a single number and writes the sequence in the shared memory

5-2: Same but frees the used resources when it's done

6-1: Multithreaded strrev 

6-2: Multiplies two matrices with each element of the product calculated by a distinct thread

7-1: Application with multiple threads trying to access finite resources (race condition). Solved by mutexes

7-2: Synchronizes n threads using a semaphore
