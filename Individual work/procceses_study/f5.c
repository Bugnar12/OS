int main(int argc, char**argv) {
 int a[4] = {1, 2, 3, 4};
 int pid;
 pid = fork();
 if(pid == 0) {
 a[2] += a[3];
 exit(0);
 }
 a[0] += a[1];
 wait(0);
 a[0] += a[2];
 printf("%d\n", a[0]);
 return 0;
}
