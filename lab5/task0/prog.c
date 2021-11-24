#include <stdio.h>

extern int open(char *path, int open_mode);
extern int close(int f);

int main(int argc, char *argv[]) {
    if (argc != 2)
        return 1;

    int fd = open(argv[1], 0);
    printf("The corresponding file descriptor is %d\n", fd);
    
    if (close(fd) > -1)
        printf("CLOSING DONE\n");
    else
        printf("CLOSING FAILED\n");

    return 0;
}