#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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

int main(int argc , char **argv) {
    if (argc < 3) {
        printf("Please provide 2 files\n");
        return 0;
    }

	FILE *output = stdout;
    FILE *originFile = fopen(argv[1], "rb");
    FILE *newFile = fopen(argv[2], "rb+");
    long len_originFile = calculateFileLen(originFile);
    long len_newFile = calculateFileLen(newFile);
    long overallSize = findMaxSize(len_originFile, len_newFile);

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
        }
    }
    list_print(diff_list , output);
    list_free(diff_list);
    return 0;
}