#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <error.h>
#include <errno.h>

int main(int argc, char *argv[])
{
	int f = open(argv[1], O_RDONLY);
	if(f < 0)
	{
		perror("Can't open file to read");
		return errno;
	}

	int g = open(argv[2], O_WRONLY);
	if(g < 0)
	{
		perror("Can't open file to write");
		return errno;
	}

	char str[50];
	int size;
	while(size = read(f, str, 50))
	{
		if(write(g, str, size) == -1)
		{
			perror("Error");
			return errno;
		}
	}

	if(size < 0)
	{
		perror("error");
		return errno;
	}

	close(f);
	close(g);

	return 0;
}