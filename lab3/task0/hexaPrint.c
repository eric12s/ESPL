#include <stdio.h>
#include <stdlib.h>

void PrintHex(char *buffer, size_t length) {
    for (int i = 0; i < length; i++)
        printf("%02X ", (unsigned char)buffer[i]);
}

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("Please provide a file name");
        return 0;
    }

    char *fileName = argv[1];
    FILE *file = fopen(fileName, "r");
    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *binaryVal = malloc(fileSize + 1);
    fread(binaryVal, fileSize, 1, file);
    binaryVal[fileSize] = 0;

    PrintHex(binaryVal, fileSize);
    printf("\n");

    if (binaryVal != NULL)
        free(binaryVal);

    return 0;
}