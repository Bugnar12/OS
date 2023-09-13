#include<stdio.h>
#include<unistd.h>
int main(int argc, char** argv) {
 printf("%d/%d before\n", getpid(), getppid());
 fork();
 printf("%d/%d after\n", getpid(), getppid());
 return 0;
}

