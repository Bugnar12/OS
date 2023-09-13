#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
	fork();
	wait(0);
	fork();
	wait(0);
	fork();
	printf("%d ", getpid());

	return 0;
}
