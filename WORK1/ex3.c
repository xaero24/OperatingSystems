#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int main()
{
    int input[]={2,2,3,0,0,0,1,0,0}, nodeCount = sizeof(input)/sizeof(int), *children;
    int count, index = 0, status, pid;

    for(int i=0; i<nodeCount; i++)
    {
        index=0;
        printf("Process number %d has pid= %d\n", i, getpid());
        for(int j=0; j<input[i]; j++){
            pid=fork();
            if(pid==0) {
                printf("I am process with pid= %d and my parent is pid= %d\n", getpid(), getppid());
            }
        }
        for(int j=0; j<input[i]; j++)
            waitpid(-1, &status, WNOHANG);
    }
	return 0;
}