#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>

#define FIFO_AB "fifoAB"
#define FIFO_BA "fifoBA"

int main() {
    // Create FIFOs
    mkfifo(FIFO_AB, 0666);
    mkfifo(FIFO_BA, 0666);

    pid_t pidA, pidB;
    int n, s;
    int fdAB, fdBA;

    pidA = fork();
    if (pidA == 0) {
        // Process A

        // Open FIFOs
        fdAB = open(FIFO_AB, O_WRONLY);
        fdBA = open(FIFO_BA, O_RDONLY);

        while (1) {
            // Read n from the user
            printf("Enter a number greater than 50 and multiple of 3: ");
            scanf("%d", &n);
            if (n <= 50 || n % 3 != 0) {
                printf("Invalid number. Try again.\n");
                continue;
            }

            while (1) {
                // Send n to Process B
                write(fdAB, &n, sizeof(int));

                // Receive divided number from Process B
                read(fdBA, &n, sizeof(int));
                printf("Process A received: %d\n", n);

                if (n <= 5) {
                    // Cleanup and exit
                    close(fdAB);
                    close(fdBA);
                    exit(0);
                }

                // Calculate s as a multiple of 3
                s = n % 3;
                printf("Process A sends s: %d\n", s);
                write(fdAB, &s, sizeof(int));

                // Add s to n
                n += s;

                // Print the updated value of n
                printf("Process A sends: %d\n", n);
            }
        }
    } else {
        pidB = fork();
        if (pidB == 0) {
            // Process B

            // Open FIFOs
            fdAB = open(FIFO_AB, O_RDONLY);
            fdBA = open(FIFO_BA, O_WRONLY);

            while (1) {
                // Receive number from Process A
                read(fdAB, &n, sizeof(int));
                printf("Process B received: %d\n", n);

                if (n <= 5) {
                    // Cleanup and exit
                    close(fdAB);
                    close(fdBA);
                    exit(0);
                }

                // Divide the number by 3
                n = n / 3;

                // Receive s from Process A
                read(fdAB, &s, sizeof(int));
                printf("Process B received s: %d\n", s);

                // Send divided number back to Process A
                write(fdBA, &n, sizeof(int));

                // Print the divided number
                printf("Process B sends: %d\n", n);
            }
        } else {
            // Parent process

            // Wait for both child processes to finish
            waitpid(pidA, NULL, 0);
            waitpid(pidB, NULL, 0);

            // Remove FIFOs
            unlink(FIFO_AB);
            unlink(FIFO_BA);
        }
    }

    return 0;
}
     
