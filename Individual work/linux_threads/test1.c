#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>

#define FIFO_AB "fifo_ab"
#define FIFO_BA "fifo_ba"

int main() {
    pid_t pidA, pidB;
    int fd_ab, fd_ba;
    int n, s;

    // Create FIFOs
    mkfifo(FIFO_AB, 0666);
    mkfifo(FIFO_BA, 0666);

    // Fork process A
    pidA = fork();
    if (pidA == 0) {
        // Process A

        // Open FIFOs for communication
        fd_ab = open(FIFO_AB, O_WRONLY);
        fd_ba = open(FIFO_BA, O_RDONLY);

        while (1) {
            // Receive number from process B
            read(fd_ba, &n, sizeof(n));
            printf("Process A received: %d\n", n);

            if (n <= 5) {
                break;
            }

            // Add a value s such that it is a multiple of 3
            s = n % 3;
            n += s;

            // Send the updated number to process B
            write(fd_ab, &n, sizeof(n));
            printf("Process A sent: %d\n", n);
        }

        // Cleanup and close FIFOs
        close(fd_ab);
        close(fd_ba);
        unlink(FIFO_AB);
        unlink(FIFO_BA);

        exit(0);
    }

    // Fork process B
    pidB = fork();
    if (pidB == 0) {
        // Process B

        // Open FIFOs for communication
        fd_ab = open(FIFO_AB, O_RDONLY);
        fd_ba = open(FIFO_BA, O_WRONLY);

        while (1) {
            // Receive number from process A
            read(fd_ab, &n, sizeof(n));
            printf("Process B received: %d\n", n);

            if (n <= 5) {
                break;
            }

            // Divide the number by 3
            n /= 3;

            // Send the updated number to process A
            write(fd_ba, &n, sizeof(n));
            printf("Process B sent: %d\n", n);
        }

        // Cleanup and close FIFOs
        close(fd_ab);
        close(fd_ba);
        unlink(FIFO_AB);
        unlink(FIFO_BA);

        exit(0);
    }

    // Process A and B have been created
    // Parent process continues execution
    sleep(1);

    // Open FIFOs for communication
    fd_ab = open(FIFO_AB, O_WRONLY);
    fd_ba = open(FIFO_BA, O_RDONLY);

    // Send initial number to process B
    n = 54;
    write(fd_ab, &n, sizeof(n));
    printf("Process A sent: %d\n", n);

    // Wait for process A and B to finish
    waitpid(pidA, NULL, 0);
    waitpid(pidB, NULL, 0);

    // Close FIFOs
    close(fd_ab);
    close(fd_ba);

    return 0;
}

