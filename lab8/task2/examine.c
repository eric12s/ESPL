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

void printSymbolsPerTable(Elf32_Shdr* strTable, Elf32_Shdr* currSectionHeader, char* sectionHeaderStart, char* address, int index) {
    char* section = sectionHeaderStart + currSectionHeader->sh_name;
    int size = currSectionHeader->sh_entsize;
    int numberOfEntities = currSectionHeader->sh_size / size;
    int i;
    for (i = 0; i < numberOfEntities; i++) {
        Elf32_Sym symbol = *(Elf32_Sym*)(address + currSectionHeader->sh_offset + i * size);
        char* name = address + strTable->sh_offset + symbol.st_name;
        printf("%d %x   %d   %s   %s \n", i + 1, symbol.st_value, index, section, name);
    }
}

void printSymbols(Elf32_Half e_shstrndx, Elf32_Half e_shnum, Elf32_Shdr* sectionHeaders, char  *ovAddress) {
    char* sectionHeaderStart = ovAddress + sectionHeaders[e_shstrndx].sh_offset;
    Elf32_Shdr* strTable;
    int i;
    for (i = 0; i < e_shnum; i++) {
        if (strncmp(sectionHeaderStart + sectionHeaders[i].sh_name, ".strtab", 7) == 0) {
            strTable = &sectionHeaders[i];
            int j;
            for (j = 0; j < e_shnum; j++) {
                if (sectionHeaders[j].sh_type == SHT_SYMTAB || sectionHeaders[j].sh_type == SHT_DYNSYM) {
                    printSymbolsPerTable(strTable, &sectionHeaders[j], sectionHeaderStart, ovAddress, j);
                    printf("------------------------------------------------------------------------------------------------\n");
                }
            }
            break;
        }
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
    printSymbols(elfHeader.e_shstrndx, elfHeader.e_shnum, sectionHeaders, address);
    free(sectionHeaders);

    return 0;
}