#include <stdio.h>
#include <unistd.h>

int main(int argc, char** argv)
{
	int i;
	i = fork();
	if(i)
		printf("salut");
	return 0;
}
