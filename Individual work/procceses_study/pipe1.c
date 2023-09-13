#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
	int a[4] = {1, 2, 3, 4};
	int pid, p[2];

	pipe(p); //create the pipe
		 //p will contain 2 numbers : one for reading from the pipe, another for writing
		 //parent created the pipe	

	pid = fork(); //here the child HAS INHERITED the pipe
	if(pid == 0) //means we are in the child process
	{
		close(p[0]); 
		a[2] += a[3];
		write(p[1], &a[2], sizeof(int));
		close(p[1]);
		exit(0);
	}
	close(p[1]);
	a[0] += a[1];
	read(p[0], &a[2], sizeof(int));
        close(p[0]);	
	wait(0);i
	a[0] += a[2];
	printf("%d\n", a[0]);
	return 0;
}
