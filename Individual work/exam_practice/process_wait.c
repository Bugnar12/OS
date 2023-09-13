#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main()
{
	int i;
	for(i = 0; i < 12; i++)
	{
		if(fork() == 0)
		{
			exit(0);
		}
		if(i % 3 == 0){
			printf("%d ", getpid());
			wait(0);
		}
	}
	printf("%d ", getpid());
	return 0;
}
