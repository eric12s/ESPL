#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

typedef struct diff {
    long offset; /* offset of the difference in file starting from zero*/
    unsigned char orig_value;     /* value of the byte in ORIG */
    unsigned char new_value;     /* value of the byte in NEW */
} diff;

typedef struct node node;
 
struct node {
    diff *diff_data; /* pointer to a struct containing the offset and the value of the bytes in each of the files*/
    node *next;
};

void list_print(node *diff_list, FILE* output) {
    /* Print the nodes in diff_list in the following format: byte POSITION ORIG_VALUE NEW_VALUE. 
    Each item followed by a newline character. */
    node *curr = diff_list;
    while (curr != NULL) {
        int currOffset = curr->diff_data->offset;
        fprintf(output , "byte %d %02x %02x\n", currOffset, curr->diff_data->orig_value, curr->diff_data->new_value);
        curr = curr->next;
    }
}
 
node* list_append(node* diff_list, diff* data) {
    /* Add a new node with the given data to the list,
        and return a pointer to the list (i.e., the first node in the list).
        If the list is null - create a new entry and return a pointer to the entry.*/
    node *newNode = (node*) malloc(sizeof(node));
    newNode->diff_data = data;
    newNode->next = NULL;

    if (diff_list != NULL) {
        newNode->next = diff_list;
    }

    return newNode;
}

void list_free(node *diff_list) {
    /* Free the memory allocated by and for the list. */
    node *curr = diff_list;
    while (curr != NULL){
        diff_list = diff_list->next;
        free(curr->diff_data);
        free(curr);
        curr = diff_list;
    }
}

void list_print_only_first(node *diff_list, FILE* output, int maxPrint) {
    node *curr = diff_list;
    while (curr != NULL && maxPrint > 0) {
        int currOffset = curr->diff_data->offset;
        fprintf(output , "byte %d %02x %02x\n", currOffset, curr->diff_data->orig_value, curr->diff_data->new_value);
        curr = curr->next;
        maxPrint--;
    }
}

void printNumberOfDifferences(node *diff_list, FILE* output) {
    int i = 0;
    node *curr = diff_list;
    while (curr != NULL) {
        i++;
        curr = curr->next;
    }
    fprintf(output, "%d\n", i);
}
    
long calculateFileLen(FILE *file) {
    fseek(file , 0 , SEEK_END);
    long len = ftell(file);
    fseek(file , 0 , SEEK_SET);

    return len;
}

long findMaxSize(long len1, long len2) {
    if (len1 < len2)
        return len2;

    return len1;
}

int legal_int(char *str) {
    while (*str)
        if (!isdigit(*str++))
            return 0;
    return 1;
}

void restore (node* diff_list, FILE* file, int maxNumberOfChanges){
    node* curr = diff_list;
    while (curr != NULL && maxNumberOfChanges > 0){
        fseek(file, curr->diff_data->offset, SEEK_SET);
        fwrite(&curr->diff_data->orig_value, 1, 1, file);
        curr = curr->next;
        maxNumberOfChanges--;
    }
}

int main(int argc , char **argv) {
    int oFlag = 0; int tFlag = 0; int kFlag = 0;
    int outputFile = 0; int firstNDifferences = 0;
    int originFileIndex = 0; int newFileIndex = 0;
    int rFlag = 0; int numberOfChanges = -1;
	for (int i = 0; i < argc; i++) {
        if (strcmp(argv[i], "-o") == 0) {
            if (argc <= i + 1) {
                printf("Please provide output filename!\n");
                return 0;
            }
            outputFile = i + 1;
            oFlag = 1;
            i++;
        } else if (strcmp(argv[i], "-t") == 0) {
            tFlag = 1;
        } else if (strcmp(argv[i], "-k") == 0) {
            if (argc <= i + 1) {
                printf("Please provide value for -k flag!\n");
                return 0;
            }
            firstNDifferences = i + 1;
            kFlag = 1;
            i++;
        }   else if (strcmp(argv[i], "-r") == 0) {
            rFlag = 1;
            if (argc > i + 1) {
                if (legal_int(argv[i + 1]) == 1) {
                    numberOfChanges = i + 1;
                    i++;
                }
            }
        } else if (originFileIndex == 0) {
            originFileIndex = i;
        } else if (newFileIndex == 0) {
            newFileIndex = i;
        }
    }

    if (newFileIndex == 0) {
        printf("Please provide 2 files\n");
        return 0;
    }
    FILE *output = oFlag == 0 ? stdout : fopen(argv[outputFile], "w");
    FILE *originFile = fopen(argv[originFileIndex], "rb");
    FILE *newFile = fopen(argv[newFileIndex], "rb+");
    long len_originFile = calculateFileLen(originFile);
    long len_newFile = calculateFileLen(newFile);
    long overallSize = findMaxSize(len_originFile, len_newFile);
    long listSize = 0;
    node *diff_list = NULL;
    for (int i = 0; i < overallSize; i++){
        unsigned char charForOriginFile;
        unsigned char charForNewFile;
        fread(&charForOriginFile , 1 , 1 , originFile);
        fread(&charForNewFile , 1 , 1 , newFile);
        if (charForNewFile != charForOriginFile) {
            diff* diff_data = malloc(sizeof(diff));
            diff_data->offset = i;
            diff_data->orig_value = charForOriginFile;
            diff_data->new_value = charForNewFile;
            diff_list = list_append(diff_list, diff_data);
            listSize++;
        }
    }   
    if (tFlag == 0 && kFlag == 0 && rFlag == 0)
        list_print(diff_list, output);
    else if (tFlag == 1)
        printNumberOfDifferences(diff_list, output);
    else if (kFlag == 1)
        list_print_only_first(diff_list, output, atoi(argv[firstNDifferences]));
    else {
        long maxNumberOfChanges;
        maxNumberOfChanges = listSize;
        if (numberOfChanges != -1)
            sscanf(argv[numberOfChanges], "%ld", &maxNumberOfChanges);
        restore(diff_list, newFile, maxNumberOfChanges);
    }
    list_free(diff_list);
    fclose(output);
    return 0;
}