#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#define READ 0
#define WRITE 1

int main(int argc, char**argv)
{
    int N, i, cpid, fpid, status, *pids, count=1;
    int ptc[2], ctp[2];
    pipe(ptc);
    pipe(ctp);
    fpid = getpid();

    printf("Enter a number: \n");
    scanf("%d", &N);
    
    for (i=0; i<N; i++){
        cpid=fork();
        if(cpid!=0){
            close(ptc[WRITE]);
			read(ptc[READ], &count, sizeof(int));
            close(ctp[WRITE]);
            read(ctp[READ], &count, sizeof(int)); 
            break;
        }
        else{
            count++;
            close(ptc[READ]);
            write(ptc[WRITE], &count, sizeof(int));
            close(ctp[READ]);
            if (i==N-1)
                write(ctp[WRITE], &count, sizeof(int));
        }
    }
    waitpid(cpid, &status, WUNTRACED);

    if (fpid==getpid()){
        printf("I am the father, my PID is %d\n", getpid());
        printf("The number of processes created, including me, is: %d\n", count);
    }
    return 0;
}