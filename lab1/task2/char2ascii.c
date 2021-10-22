#include <stdio.h>
#include <string.h>
#include <ctype.h> 

FILE* chooseSource(int toInputFile, char *inputFileName) {
    if (toInputFile)
        return fopen(inputFileName, "r");
    return stdin;
}

void addNewLine(unsigned char input, int toOutputFile, FILE* fp) {
    if (input == '\n') {
        if (!toOutputFile)
            printf("\n");
        else
            fputs("\n", fp);
    }
}
void decimalPrint(int toOutputFile, char *outputFileName, int toInputFile, char *inputFileName) {
    unsigned char input;
    FILE *fp;
    if (toOutputFile)
        fp = fopen(outputFileName, "w");
    FILE *source = chooseSource(toInputFile, inputFileName);
    while ((input = fgetc(source)) != EOF) {
        if (toInputFile)
            if(feof(source)) {
                if(!toOutputFile)
                    printf("\n");
                break;
            }

        if (input >= ' ') {
            if (toOutputFile == 0)
                printf("%d ", input);
            else
                fprintf(fp, "%d ", (int)input);
        }
        addNewLine(input, toOutputFile, fp);
        if (toOutputFile)
            fflush(fp);
    }
}

void calcBinary(char ch, int bin[8]) {
    int decValue = ch;
    for (int i = 7; i >= 0; i--) {
        bin[i] = decValue % 2;
        decValue = decValue / 2;
    }
}

void binaryPrint(int toOutputFile, char *outputFileName, int toInputFile, char *inputFileName) {
    unsigned char input;
    FILE *fp;
    if (toOutputFile)
        fp = fopen(outputFileName, "w");
    FILE *source = chooseSource(toInputFile, inputFileName);
    while ((input = fgetc(source)) != EOF) {
        if (toInputFile)
            if(feof(source)) {
                if(!toOutputFile)
                    printf("\n");
                break;
            }

        if (input >= ' ') {
            int bin[8];
            calcBinary(input, bin);
            for (int i = 0; i < 8; i++) {
                if (!toOutputFile)
                    printf("%d", bin[i]);
                else
                    fprintf(fp, "%d", bin[i]);
            }
            if (!toOutputFile)
                printf(" ");
            else
                fputs(" ", fp);
        }
        addNewLine(input, toOutputFile, fp);
        if (toOutputFile)
            fflush(fp);
    }
}

void lowerCasePrint(int toOutputFile, char *outputFileName, int toInputFile, char *inputFileName) {
    unsigned char input;
    FILE *fp;
    if (toOutputFile)
        fp = fopen(outputFileName, "w");
    FILE *source = chooseSource(toInputFile, inputFileName);
    while ((input = fgetc(source)) != EOF) {
        if (toInputFile)
            if(feof(source)) {
                if(!toOutputFile)
                    printf("\n");
                break;
            }

        if (input >= ' ') {
            unsigned char lowerCase = tolower(input);
            if (!toOutputFile)
                printf("%c", lowerCase);
            else
                fputc(lowerCase, fp);
        }
        addNewLine(input, toOutputFile, fp);
        if (toOutputFile)
            fflush(fp);
    }
}

int main(int argc, char **argv) {
    int inputFile = 0;
    int outputFile = 0;
    int isInputFile = 0;
    int isOutputFile = 0;
    int isBFlag = 0;
    int isCFlag = 0;

    for (int i = 0; i < argc; i++) {
        if (strcmp(argv[i], "-i") == 0) {
            if (argc <= i + 1) {
                printf("Please provide input filename!");
                return 0;
            }
            inputFile = i + 1;
            isInputFile = 1;
            i++;
        } else if (strcmp(argv[i], "-o") == 0) {
            if (argc <= i + 1) {
                printf("Please provide output filename!");
                return 0;
            }
            outputFile = i + 1;
            isOutputFile = 1;
            i++;
        } else if (strcmp(argv[i], "-c") == 0) {
            isCFlag = 1;
        } else if (strcmp(argv[i], "-b") == 0) {
            isBFlag = 1;
        }
    }

    if (isBFlag) {
        binaryPrint(isOutputFile, argv[outputFile], isInputFile, argv[inputFile]);
        return 0;
    } if (isCFlag) {
        lowerCasePrint(isOutputFile, argv[outputFile], isInputFile, argv[inputFile]);
        return 0;
    }
    decimalPrint(isOutputFile, argv[outputFile], isInputFile, argv[inputFile]);
    return 0;
}