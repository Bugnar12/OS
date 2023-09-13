#include <stdio.h>
#include <unistd.h>

int main()
{
	int i;
	for(i = 0 ; i < 3; i++)
	{
		if(fork() && i % 2 == 1)
		{
			break;
		}
	}
	printf("%d ", getpid());


}
