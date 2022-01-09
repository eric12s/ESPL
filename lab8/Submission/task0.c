#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <ctype.h>
#include <fcntl.h>
#include "elf.h"

Elf32_Shdr *getSectionHeaders(Elf32_Ehdr *elfHeader, char *address) {
    Elf32_Shdr *sectionHeaders = (Elf32_Shdr *)malloc(sizeof(Elf32_Shdr) * elfHeader->e_shnum);
    int i;
    for (i = 0; i < elfHeader->e_shnum; i++) {
        int offset = elfHeader->e_shoff + i * sizeof(Elf32_Shdr);
        sectionHeaders[i] = *(Elf32_Shdr*)(address + offset);
    }
    return sectionHeaders;
}

void print_data_encoding_format(Elf32_Ehdr *header) {
    if (header->e_ident[5] == ELFDATA2LSB)
        printf("The dataata: Two's complement, little-endian\n");
    else if (header->e_ident[5] == ELFDATA2MSB)
        printf("The data: Two's complement, big-endian\n");
    else
        printf("The data: Couldn't find the right format\n");
}

void printSizesForSectionHeaders(Elf32_Shdr *sectionHeaders, int numOfSectionHeaders) {
    int i;
    for (i = 0; i < numOfSectionHeaders; i++)
        printf("Size of section %d: %d bytes\n", i + 1, sectionHeaders[i].sh_size);
}

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("Please provide a file name\n");
        return 0;
    }
    FILE* file = fopen(argv[1], "r");
    fseek(file, 0, SEEK_END);
    int size = ftell(file);
    fseek(file, 0, SEEK_SET);
    int fd = open(argv[1], O_RDONLY);
    char* address = mmap(NULL, size, PROT_READ, MAP_PRIVATE, fd, 0);
    char buf[100];
    size_t sizeChar = 3;
    strncpy(buf, address + 1, sizeChar);
    buf[3] = 0;
    if (strncmp(buf, "ELF", sizeChar) != 0) {
        printf("The file is not elf\n");
        return 0;
    }
    printf("%s\n", buf);

    Elf32_Ehdr elfHeader = *(Elf32_Ehdr *)address;
    Elf32_Shdr *sectionHeaders = getSectionHeaders(&elfHeader, address);
    print_data_encoding_format(&elfHeader);
    printf("The entry point: 0x%x\n", elfHeader.e_entry);
    printf("The file offset: %d\n", elfHeader.e_shentsize);
    printf("The number of section header entries: %d\n", elfHeader.e_shnum);
    printSizesForSectionHeaders(sectionHeaders, elfHeader.e_shnum);
    printf("The index of shstrtab in section header: %d\n", elfHeader.e_shstrndx);

    free(sectionHeaders);

    return 0;
}