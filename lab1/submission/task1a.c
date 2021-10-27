#include <stdio.h>

int main(int argc, char **argv) {
    unsigned char input;
        while ((input = fgetc(stdin)) != EOF) {
            if (input >= ' ')
                printf("%d ", input);
            if (input == '\n')
                printf("\n");
        }
        printf("\n");
    return 0;
}