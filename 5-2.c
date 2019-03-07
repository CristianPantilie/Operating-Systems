#include <sys/types.h>
#include <sys/mman.h>
#include <err.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <wait.h>

int main(int argc, char *argv[])
{
        const char *name = "myshm";
        const int PAGE = getpagesize();

        size_t size = PAGE * (argc - 1);
        int fd = shm_open(name, O_CREAT|O_RDWR, 0);

        ftruncate(fd, size);

        pid_t pids[argc];

        for(int i = 1; i < argc; i++){
                pids[i] = fork();

                if(pids[i] == 0){
                        int n = atoi(argv[i]);
                        
                        int *ptr = mmap(0, PAGE, PROT_WRITE, MAP_SHARED, fd, (i - 1) * PAGE);
                        int poz = 0;

                        while(n != 1)
                        {
                           ptr[poz++] = n;
                           if(n % 2 == 1)
                                n = 3 * n + 1;
                           else
                                n = n / 2;
                        }
                        ptr[poz++] = 1;

                        printf("\nChild %d finished while parent %d was waiting\n\n", getpid(), getppid());

                        exit(0);
                }
               
       }   
  
        for(int i = 1; i < argc; i++){
                wait(0);
        }

        int *sptr = mmap(0, size, PROT_READ, MAP_SHARED, fd, 0);

        for(int i = 1; i < argc; i++)
        {
            for(int j = (i - 1) * PAGE/sizeof(int) + 1;   ; j++)
            {
                if(sptr[j] == 1)
                {
                    printf("%d\n", sptr[j]);
                    break;
                }
                else
                    printf("%d, ", sptr[j]);        
            }
        }

        munmap(sptr, size);
        shm_unlink(name);

        return 0;
}

