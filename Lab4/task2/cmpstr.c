#include <stdio.h>

int length_of_string(char*p) {
    int count = 0;
    while (*p != '\0') {
        count++;
        p++;
    }
    return count;
}

int calcDiff (char a, char b) {
    int aD = a;
    int bD = b;
    return aD-bD;
}

int cmpstr(char* firstS, char* secondS) {
    int firstS_size = length_of_string(firstS);
    int secondS_size = length_of_string(secondS);

    int size = firstS_size;
    if (firstS_size < secondS_size) {
        size = secondS_size;
    }
    int output = 0;

    for (int i = 0; i < size; i++) {
        if (firstS[i] != secondS[i]) {
            output = calcDiff(firstS[i], secondS[i]);
            break;
        }
    }

    return output;
}