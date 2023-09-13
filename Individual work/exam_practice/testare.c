#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	int i;
	for(i = 0; i < 3; i++)
	{
		fork();
		execlp("ls", "ls", "/", NULL);
	}
	printf("%d ", getpid());
	return 0;
}

