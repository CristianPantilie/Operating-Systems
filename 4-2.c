#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>

int main(int argc, char *argv[]){

	pid_t pid = fork();

	int n = atoi(argv[1]);

	if(pid < 0)
		return errno;
	else if (pid == 0)
	{
		while(n > 1)
		{
			if(n%2 == 1)
				n = 3 * n + 1;
			else
				n = n / 2;
		}
		
		printf("Child %d finished", getpid());	
	}
		




	return 0;
}
