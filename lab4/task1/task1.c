#include <stdio.h>

extern int funcA(char *ch);

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stdout, "Usage: task0 arg1 \n");
        return 0;
    }

    int res = funcA(argv[1]);
    printf("The solution is %d\n", res);

    return 0;
}