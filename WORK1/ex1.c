#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char** argv)
{
    int pid, child, status;

    child = fork();
    if(child == 0){
        printf("It's a child process- My pid is: %d. My parent process is: %d\n", getpid(), getppid());
    }
    else{
        printf("It's a parent process- My pid is: %d. My child process is: %d\n", getpid(), child);
        pid = wait(&status);
    }
}