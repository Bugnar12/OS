#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

void f(int n){
	if(n > 0 || fork() == 0)
	{
		printf("Process created\n");
		f(n-1);
		exit(0);
	}
	wait(0);
}

int main(int argc, char** argv)
{
	f(3);
	return 0;
}
