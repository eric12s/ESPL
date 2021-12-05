#include <linux/limits.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "LineParser.h"
#include <stdlib.h>

void handleCd(cmdLine *cmdLine);

void execute(cmdLine *cmdLine) {
    int result;
    int pid = fork();
    if (pid == 0) {
            result = execvp(cmdLine->arguments[0], cmdLine->arguments);

        if (result == -1) {
            perror("ERROR");
        }
        _exit(result);
    } else if(pid > 0) {
        if (cmdLine->blocking) {
            waitpid(pid, &result, 0);
        }
    }
}

int main(int argc, char const *argv[]){
    char input[2048];
    char buff[PATH_MAX];
    int const MAX_LINE_SIZE = 2048;

    while (1) {
        getcwd(buff, PATH_MAX);
        printf("%s> ", buff);
        fgets(input, MAX_LINE_SIZE, stdin);

        if (strcmp(input, "quit\n") == 0)
            break;

        cmdLine *line = parseCmdLines(input);
        if (strcmp("cd", line->arguments[0]) == 0)
            handleCd(line);
        else
            execute(line);
        freeCmdLines(line);
    }

    printf("\n");
    return 0;
}

void handleCd(cmdLine *cmdLine) {
    int result;
    if (cmdLine->argCount == 1) {
        result = chdir(getenv("HOME"));
    }
    else if (cmdLine->argCount == 2) {
        result = chdir(cmdLine->arguments[1]);
    } else {
        result = 1;
    }

    if (result) {
        perror("ERROR");
    }
}