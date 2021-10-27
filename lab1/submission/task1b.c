#include <stdio.h>
#include <string.h>

void decimalPrint() {
    unsigned char input;
        while ((input = fgetc(stdin)) != EOF) {
            if (input >= ' ')
                printf("%d ", input);
            if (input == '\n')
                printf("\n");
        }
    printf("\n");
}

void calcBinary(char ch, int bin[8]) {
    int decValue = ch;
    for (int i = 7; i >= 0; i--) {
        bin[i] = decValue % 2;
        decValue = decValue / 2;
    }
}

int main(int argc, char **argv) {
    if (argc == 1 || strcmp(argv[1], "-b") != 0) {
        decimalPrint();
        return 0;
    }
    unsigned char input;
    while ((input = fgetc(stdin)) != EOF) {
        if (input >= ' ') {
            int bin[8];
            calcBinary(input, bin);
            for (int i = 0; i < 8; i++)
                printf("%d", bin[i]);
            printf(" ");
        }
        if (input == '\n')
            printf("\n");
    }
    printf("\n");
    return 0;
}