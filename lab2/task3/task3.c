#include <stdio.h>
#include <stdlib.h>

#define ARRAY_MAX_SIZE 10

typedef struct fun_desc
{
    char *name;
    void (*fun)(char);
} fun_desc;

void echo_printer(char c);
void binary_printer(char c);
void lower_to_upper_printer(char c);
void ascii_printer(char c);

void string_printer(char *array, void (*f)(char));

void bitwise_or(char *s);
void string_reader(char *s);


int main(int argc, char **argv){
	struct fun_desc MyFunctions[] = {
        {"echo printer", echo_printer},
        {"ascii printer", ascii_printer},
        {"binary printer", binary_printer},
        {"lower to upper printer", lower_to_upper_printer},
    };
    int NumberOfFunctions = sizeof(MyFunctions) / sizeof(fun_desc);

    char input[ARRAY_MAX_SIZE];
    printf("Enter an input:\n");
    string_reader(input);

    printf("These are the available functions:\n");
    for (int i = 0; i < NumberOfFunctions; i++)
        printf("%d -- %s\n", i, MyFunctions[i].name);
    printf("%d -- %s\n", NumberOfFunctions, "bitwise_or");

    printf("Please choose a number from the menu:\n");
    int numUserChoise;
    char userChoise[4];
    printf("Option: ");
    string_reader(userChoise);
    numUserChoise = atoi(userChoise);
    while (numUserChoise != EOF) {
        if (numUserChoise < 0 || numUserChoise > NumberOfFunctions)
            printf("Please select 0-4 or CTRL-D to exit.\n");
        else if (numUserChoise == 4)
            bitwise_or(input);
        else
            string_printer(input, MyFunctions[numUserChoise].fun);
        printf("Option: ");
        string_reader(userChoise);

        numUserChoise = atoi(userChoise);
    }
    printf("DONE.");
}