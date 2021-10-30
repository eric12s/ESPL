#include <stdio.h>
#include <string.h>

#define ARRAY_MAX_SIZE 10

void binary_printer(char c);

// void binary_printer(char c) {
//     int decValue = c;
//     int bin[8];
//     for (int i = 7; i >= 0; i--) {
//         bin[i] = decValue % 2;
//         decValue = decValue / 2;
//     }

//     for(int i = 0; i < 8; i++)
//         printf("%d", bin[i]);
//     printf("\n");
// }

void string_reader(char *s) {
    fgets(s, ARRAY_MAX_SIZE + 1, stdin);
    s[strcspn(s, "\n")] = 0;
}

void bitwise_or(char *s) {
    char bitWise = 0;
    int counter = 0;
    while (*s && counter <= ARRAY_MAX_SIZE) {
        bitWise |= *s;
        s++;
        counter++;
    }
    binary_printer(bitWise);
}

// int main(int argc, char **argv){
//     bitwise_or("abd");
//     return 0;
// }