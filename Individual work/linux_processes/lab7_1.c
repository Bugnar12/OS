#include <signal.h>

#include <stdio.h>

#include <sys/syscall.h>

#include <sys/types.h>

#include <unistd.h>



void testsig()

{

    printf("HANDLER: TID=%ld\n", syscall(__NR_gettid));

}



int main()

{

    printf("MAIN: PID=%d, TID=%ld\n", getpid(), syscall(__NR_gettid));

    signal(SIGHUP, testsig);

    for (;;) {sleep(2);}

}
