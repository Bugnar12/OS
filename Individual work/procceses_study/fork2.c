#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char** argv)
{
	int i, j, k;
	i = fork();
	if((j = fork()))
		k = fork();
	printf("%d %d %d %d %d", i, j, k, getpid(), getppid());
	
	return 0;
}
