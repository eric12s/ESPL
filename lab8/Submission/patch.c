#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>

int main(int argc, char **argv) {
    char *source_file = argv[1];
    char *source_pos = argv[2];
    char *dest_file = argv[4];
    char *dest_pos = argv[5];

    int source_fd = open(source_file, O_RDONLY);
    int dest_fd = open(dest_file, O_RDWR);
    if (source_fd == -1 || dest_fd == -1) {
        printf("Invalid file input\n");
        return 0;
    }

    struct stat source_stat;
    struct stat dest_stat;
    fstat(source_fd, &source_stat);
    fstat(dest_fd, &dest_stat);

    char *mappedSource = mmap(NULL, source_stat.st_size, PROT_READ, MAP_PRIVATE, source_fd, 0) + atoi(dest_pos);
    char* mappedDest = mmap(NULL, dest_stat.st_size, PROT_WRITE, MAP_SHARED, dest_fd, 0) + atoi(source_pos);


    memcpy(mappedDest, mappedSource, atoi(argv[3]));

    close(source_fd);
    close(dest_fd);

    return 0;
}