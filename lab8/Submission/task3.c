#include<stdio.h>
#include<stdlib.h>

int fib(int limit) {
    if (limit == 0)
        return -1;

    int prev = 1;
    int curr = 1;

    for (int i = 0; prev + curr < limit; i++) {
        int tmp = curr;
        curr = curr + prev;
        prev = tmp;
    }
    return curr;
}

int main(int argc, char **argv) {
    int numOfValues = atoi(argv[1]);
    printf("%d\n", fib(numOfValues));
    return 0;
}