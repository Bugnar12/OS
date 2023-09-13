#include <stdio.h>
#include <unistd.h>
int main(int argc, char** argv) {
 execlp("grep", "grep", "-E", "/an1/gr211/", "/etc/passwd", NULL);
 printf("If grep is in the PATH, then execlp succeeds, and this will never be printed.\n");
 return 0;
}

