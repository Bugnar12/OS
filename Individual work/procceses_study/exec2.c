#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
int main(int argc, char** argv) {
 int pid = fork();
 if(pid == 0) {
	 printf("Entering the child process and greping some things\n");
	 execlp("grep", "grep", "^sshd:", "/etc/passwd", NULL);
 	 exit(1);
 }
 // do some other work in the parent
 printf("Now in the parent process : rest of the code is working ");
 wait(0);
 return 0;
}
