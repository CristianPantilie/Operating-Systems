#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>


void collatz(int n){
	printf("n = %d:  ", n);
	while(n > 1){
		if(n%2 == 1)
			n = 3 * n + 1;
		else
			n = n / 2;

		printf("%d ", n);
		}
}

int main(int argc, char *argv[]){

	pid_t pids[argc];

	for(int i = 1; i < argc; i++){
		
		int n = atoi(argv[i]);

		pids[i] = fork();

		if(pids[i] < 0)
			return errno;
		else if(pids[i] == 0){
			//child
			collatz(n);
			
			printf("\nChild %d finished while parent %d was waiting\n\n", getpid(), getppid());
			exit(0);
		}
	}	
		
	for(i = 1; i < argc; i++){
		pid_t pid = wait(0);
	}


	return 0;
}