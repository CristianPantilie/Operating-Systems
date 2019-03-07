#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <error.h>
#include <errno.h>

int main()
{
	write(STDOUT_FILENO, "Hello world", 11);

	return 0;
}