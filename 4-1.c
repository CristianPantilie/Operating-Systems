#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <time.h>


int main(int argc, char *argv[]){


	
	pid_t pid = fork();

	if(pid < 0)
		return errno;
	else if(pid == 0){
		
		execve("/bin/ls", argv, NULL);
	}
	else{
		printf("Asta e copilul: %d\n", getpid());
		printf("Asta e parintele: %d\n\n\n\n", getppid());
	}
	

	return 0;
}


