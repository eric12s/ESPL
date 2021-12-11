#include <linux/limits.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "LineParser.h"
#include <stdlib.h>
#include <fcntl.h>

void handleCd(cmdLine *cmdLine);
int historyCount = 0;
int isHistoryFull = 0;
void handleHistory();
int isExclamationMarkPrefix(char *command);
void handleExclamationMark(char *history[], char *command);
void handleIO(cmdLine *cmd_line, char io_need_close[]) ;
void closeIO(char io_need_close[]);

int pipefd[2];

void execute(cmdLine *cmdLine) {
    int result;
    char alreadyUsedIO[2] = {0, 0};
    pipe(pipefd);
    int numOfCommands = 1;
    if (cmdLine->next)
        numOfCommands = 2;
    int i;
    for (i = 0; i < numOfCommands; i ++) {
        int pid = fork();
        if (pid == 0) {
            handleIO(cmdLine, alreadyUsedIO);
            result = execvp(cmdLine->arguments[0], cmdLine->arguments);
            if (result == -1) {
                perror("ERROR");
            }
            closeIO(alreadyUsedIO);
            _exit(result);
        } else if(pid > 0) {
            if (cmdLine->blocking) {
                waitpid(pid, &result, 0);
            }
        }
        if (cmdLine->next)
            close(pipefd[1]);
        else if (cmdLine->idx == 1)
            close(pipefd[0]);
        cmdLine = cmdLine->next;
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

void handleIO(cmdLine *cmd_line, char alreadyUsedIO[]) {
    if (cmd_line->outputRedirect) {
        close(STDOUT_FILENO);
        dup2(open(cmd_line->outputRedirect, O_WRONLY | O_CREAT, 0666), STDOUT_FILENO);
        alreadyUsedIO[1] = 1;
    }
    if (cmd_line->inputRedirect) {
        close(STDIN_FILENO);
        dup2(open(cmd_line->inputRedirect, O_RDONLY), STDIN_FILENO);
        alreadyUsedIO[0] = 1;
    } if (cmd_line->idx == 1) {
        close(STDIN_FILENO);
        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[0]);
    } if (cmd_line->next) {
        close(STDOUT_FILENO);
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);
    }
}

void closeIO(char toClose[]) {
    if (toClose[0])
        close(STDIN_FILENO);
    if (toClose[1])
        close(STDOUT_FILENO);
}