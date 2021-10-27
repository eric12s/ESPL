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

void decimalPrint(unsigned char input, FILE* fp, int toOutputFile) {
    if (input >= ' ') {
        if (!toOutputFile)
            printf("%d ", input);
        else
            fprintf(fp, "%d ", (int)input);
    }
}

void calcBinary(char ch, int bin[8]) {
    int decValue = ch;
    for (int i = 7; i >= 0; i--) {
        bin[i] = decValue % 2;
        decValue = decValue / 2;
    }
}

void binaryPrint(unsigned char input, FILE* fp, int toOutputFile) {
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
}

void lowerCasePrint(unsigned char input, FILE* fp, int toOutputFile) {
    if (input >= ' ') {
        unsigned char transformed;
        if (isupper(input))
            transformed = tolower(input);
        else
            transformed = toupper(input);
        if (!toOutputFile)
            printf("%c", transformed);
        else
            fputc(transformed, fp);
    }
}

void executeLogic(int toOutputFile, char *outputFileName, int toInputFile, char *inputFileName, int isFlag) {
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
        if (isFlag == 1) 
            binaryPrint(input, fp, toOutputFile);
        else if (isFlag == 2)
            lowerCasePrint(input, fp, toOutputFile);
        else
            decimalPrint(input, fp, toOutputFile);        
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
    int isFlag = 0;

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
            isFlag = 2;
        } else if (strcmp(argv[i], "-b") == 0) {
            isFlag = 1;
        }
    }
    
    executeLogic(isOutputFile, argv[outputFile], isInputFile, argv[inputFile], isFlag);
    return 0;
}