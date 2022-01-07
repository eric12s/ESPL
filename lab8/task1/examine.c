#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
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

void printSections(Elf32_Shdr* shdrs, Elf32_Half shstrtabIndex, int shnum, char* ovAddress) {
    char* sectionStrTable = ovAddress + shdrs[shstrtabIndex].sh_offset;
    for (int i = 0; i < shnum; i++) {
        char* name = sectionStrTable + shdrs[i].sh_name;
        Elf32_Addr address = shdrs[i].sh_addr;
        Elf32_Off offset = shdrs[i].sh_offset;
        Elf32_Word size = shdrs[i].sh_size;
        printf("[%d] %s   %x   %d   %d \n", i + 1, name, address, offset, size);
    }
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

    Elf32_Ehdr elfHeader = *(Elf32_Ehdr *)address;
    Elf32_Shdr *sectionHeaders = getSectionHeaders(&elfHeader, address);
    printSections(sectionHeaders, elfHeader.e_shstrndx, elfHeader.e_shnum, address);
    free(sectionHeaders);

    return 0;
}