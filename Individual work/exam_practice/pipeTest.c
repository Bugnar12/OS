#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

int main()
{
	int p[2];
	char buf[10];
	int n;
	strcpy(buf,"mama");
	pipe(p);
	n = read(p[0], buf, 10);
	printf("%d\n", n);

	return 0;
}
