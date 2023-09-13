#include <unistd.h>
#include <stdlib.h>

int main() {
    // Using execlp to execute the cat command with output redirection
    execlp("cat", "cat", "d.txt", "> e.txt", NULL);

    // Handle any error if execlp fails to execute
    perror("execlp");
    exit(EXIT_FAILURE);
}

