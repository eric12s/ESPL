#include <stdio.h> 
  
void string_printer(char *array, void (*func_ptr) (char)) {
    while(*array) {
        (*func_ptr)(*array);
        printf(" ");
        array++;
    }
    printf("\n");
}

int main(int argc, char **argv) {
}
