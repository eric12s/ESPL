#include <stdio.h>
#include <string.h>
#include <ctype.h>

void echo_printer(char c) {
    printf("%c", c);
}

void ascii_printer(char c) {
    printf("%d ", c);
}

void binary_printer(char c) {
    int decValue = c;
    int bin[8];
    for (int i = 7; i >= 0; i--) {
        bin[i] = decValue % 2;
        decValue = decValue / 2;
    }

    for(int i = 0; i < 8; i++)
        printf("%d", bin[i]);
    printf("\n");
}

void lower_to_upper_printer(char c) {
    unsigned char transformed;
    if (isupper(c))
        transformed = tolower(c);
    else
        transformed = toupper(c);
    printf("%c", transformed);
}