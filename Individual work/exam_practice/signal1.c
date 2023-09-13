#include <stdio.h>
#include <signal.h>
void f(int sgn) //sgn - number of signal
{
	printf("Noooo waaaaay!\n");
}

int main (int argc, char** argv)
{
	// be called when we ctrl c
	signal (SIGINT, f);
	while (1);
	return 0;
}
