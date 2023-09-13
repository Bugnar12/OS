#include<stdio.h>
#include<unistd.h>
int main(int argc, char** argv) {
 int i;
 for(i=0; i<3; i++) {
 fork();
 }
 printf("there will be 7 procceses");
 return 0;
}
