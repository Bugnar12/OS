#include <stdio.h>
#include <unistd.h>

int main(int argc, char** argv)
{
	if(fork() || fork())
		fork();
}
