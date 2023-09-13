#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    int i, counter = 0;

    for (i = 0; i < 4; i++) {
	printf("%d ", getpid());
        if (fork() && i % 2 == 1) {	
	 	break;
  	}
    }

    return 0;
}
