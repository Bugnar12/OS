#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
	int fd[2];
	pid_t pid;

	if(pipe(fd) == -1){
		perror("pipe failure");
		return 1;
	}
	pid = fork();
	if(pid < 0){
		perror("fork failed");
		return 1;
	}

	if(pid == 0){
		close(fd[1]);
		int num1, num2;
		read(fd[0], &num1, sizeof(num1)); //read the first number
		read(fd[0], &num2, sizeof(num2)); //read the second number
		int sum = num1 + num2;
		printf("sum is : %d \n", sum);

		close(fd[0]);

	}
	else{
		close(fd[0]);

		int num1, num2;
		printf("Enter first number : ");
		scanf("%d", &num1);
		printf("Enter second number : ");
		scanf("%d", &num2);

		write(fd[1], &num1, sizeof(num1));
		write(fd[1], &num2, sizeof(num2));

		close(fd[1]);

	}
	return 0;
}
