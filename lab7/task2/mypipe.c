#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char **argv){
    int isDebug = 0;
    if (argc > 1 && strcmp(argv[1], "-d") == 0)
        isDebug = 1;

    char *cmd1[3] = {"ls", "-l", NULL};
    char *cmd2[3] = {"tail", "-n 2", NULL};
    
    
    int pid1, pid2;
    int exit_code1, exit_code2;

    int pipefd[2];
    pipe(pipefd);

    if (isDebug == 1)
        printf("(parent_process>forking…)\n");
    pid1 = fork();
    
    if (isDebug == 1 && pid1 > 0)
        printf("(parent_process>created process with id: %d)\n", pid1);

    if (pid1 == 0) {
        if (isDebug == 1) {
            printf("(child1>redirecting stdout to the write end of the pipe…)\n");
            printf("(child1>going to execute cmd: %s…)\n", cmd1[0]);
        }
        close(STDOUT_FILENO);
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);

        execvp(cmd1[0], cmd1);

    }
    if (isDebug == 1)
        printf("(parent_process>closing the write end of the pipe…)\n");

    /* when removing this, there is deadlock because of awaiting child */
    close(pipefd[1]);

    if (isDebug == 1)
        printf("(parent_process>forking…)\n");

    pid2 = fork();

    if (isDebug == 1 && pid2 > 0)
        printf("(parent_process>created process with id: %d)\n", pid2);

    if (pid2 == 0) {
        close(STDIN_FILENO);
        if (isDebug == 1)
            printf("(child2>redirecting stdin to the read end of the pipe…)\n");

        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[0]);
        if (isDebug == 1)
            printf("(child2>going to execute cmd: %s…)\n", cmd2[0]);

        execvp(cmd2[0], cmd2);

    }
    if (isDebug == 1)
        printf("(parent_process>closing the read end of the pipe…)\n");

    /* main proccess can continue without this close, the child proccess won't exit */
    close(pipefd[0]);

    if (isDebug == 1)
        printf("(parent_process>waiting for child processes to terminate…)\n");

    /*proccess keep running if removed*/
    waitpid(pid1, &exit_code1, 0);
    waitpid(pid2, &exit_code2, 0);

    if (isDebug == 1)
        printf("(parent_process>exiting…)\n");

    return 0;
}