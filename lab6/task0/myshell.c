#include <linux/limits.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "LineParser.h"

void execute(cmdLine *cmdLine) {
    int result = execvp(cmdLine->arguments[0], cmdLine->arguments);

    if (result == -1) {
        perror("ERROR");
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
        execute(line);
        freeCmdLines(line);
    }

    printf("\n");
    return 0;
}