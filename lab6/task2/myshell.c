#include <linux/limits.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "LineParser.h"
#include <stdlib.h>

void handleCd(cmdLine *cmdLine);
int historyCount = 0;
int isHistoryFull = 0;
void handleHistory();
int isExclamationMarkPrefix(char *command);
void handleExclamationMark(char *history[], char *command);

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
    char* history[256];
    int i;
    for (i = 0; i < 256; i++)
        history[i] = (char*)malloc(sizeof(cmdLine));

    while (1) {
        getcwd(buff, PATH_MAX);
        printf("%s> ", buff);
        fgets(input, MAX_LINE_SIZE, stdin);

        if (strcmp(input, "quit\n") == 0)
            break;

        cmdLine *line = parseCmdLines(input);

        input[strcspn(input, "\n")] = 0;
        if (isExclamationMarkPrefix(line->arguments[0]) == 0)
            handleExclamationMark(history, line->arguments[0]); 
        else {
            strcpy(history[historyCount], input);
            historyCount += 1;
            if (historyCount == 255) {
                historyCount = 0;
                isHistoryFull = 1;
            }
            if (strcmp("cd", line->arguments[0]) == 0)
                handleCd(line);
            else if (strcmp("history", line->arguments[0]) == 0)
                handleHistory(history);
            else
                execute(line);
        }
        freeCmdLines(line);
    }

    for (i = 0; i < 256; i++)
        free(history[i]);
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

void handleHistory(char* history[]) {
    size_t i;
    if (isHistoryFull == 0) {
        for (i = 0; i < historyCount; i++) {
            printf("%s\n", history[i]);
        }
    } else {
        for (i = historyCount; i < 256; i++) {
            printf("%s\n", history[i]);
        }
        for (i = 0; i < historyCount; i++) {
            printf("%s\n", history[i]);
        }
    }
}

int isExclamationMarkPrefix(char* command) {
    char* exclamationMark = "!";
    return strncmp(exclamationMark, command, strlen(exclamationMark));
}

void handleExclamationMark(char* history[], char* command) {
    memmove(command, command + 1, strlen(command));
    int historyIndex = atoi(command);
    if (historyIndex < historyCount) {
        strcpy(history[historyCount], history[historyIndex]);
        historyCount += 1;
        if (historyCount == 255) {
            historyCount = 0;
            isHistoryFull = 1;
        }
        cmdLine *line = parseCmdLines(history[historyIndex]);
        if (strcmp("cd", line->arguments[0]) == 0)
            handleCd(line);
        else if (strcmp("history", line->arguments[0]) == 0)
            handleHistory(history);
        else
            execute(line);

        freeCmdLines(line);
    }
    else
        printf("ERROR: Not enough history lines!\n");
}