#include <assert.h>
#include "../task/elf.h"
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

FILE *kfile;
elf_header header;
elf_sect_header symtab;
elf_sect_header strtab;

void test_header() {
    assert(header.magic == ELF_MAGIC);
    assert(header.wordsize == ELF_WORDSIZE_32);
    assert(header.endianness == ELF_LITTLE_ENDIAN);
    assert(header.version == 1);
    assert(header.type == ELF_TYPE_EXECUTABLE);
    assert(header.instruction_set = ELF_INSTRUCTION_SET_X86);
    assert(header.version2 == 1);
    assert(header.prog_table_entry_size == sizeof(elf_prog_header));
    assert(header.sect_table_entry_size == sizeof(elf_sect_header));
}

void test_sections() {
    elf_sect_header names_header;
    char *shstr;

    fseek(kfile, header.sect_table_offset + header.sect_table_entry_size*header.sect_names_index, SEEK_SET);
    size_t s = fread(&names_header, sizeof(elf_sect_header), 1, kfile);
    assert(s == 1);

    shstr = malloc(names_header.size);
    assert(shstr != NULL);
    fseek(kfile, names_header.offset, SEEK_SET);
    s = fread(shstr, 1, names_header.size, kfile);
    assert(s == names_header.size);

    for (int i = 0; i < header.sect_table_numentries; i++) {
        elf_sect_header sect;
        fseek(kfile, header.sect_table_offset + header.sect_table_entry_size*i, SEEK_SET);
        s = fread(&sect, sizeof(elf_sect_header), 1, kfile);
        assert(s == 1);

        if (strcmp(shstr+sect.name, ".symtab") == 0) symtab = sect;
        if (strcmp(shstr+sect.name, ".strtab") == 0) strtab = sect;
    }

    free(shstr);
}

void test_symtab() {
    char *strs;
    assert(symtab.name != 0);
    assert(strtab.name != 0);

    strs = malloc(strtab.size);
    assert(strs != NULL);

    fseek(kfile, strtab.offset, SEEK_SET);
    size_t s = fread(strs, 1, strtab.size, kfile);
    assert(s == strtab.size);

    assert(symtab.entrysize == sizeof(elf_sym));
    int n = symtab.size/symtab.entrysize;
    for (int i=0; i < n; i++) {
        elf_sym sym;
        fseek(kfile, symtab.offset+symtab.entrysize*i, SEEK_SET);
        s = fread(&sym, sizeof(elf_sym), 1, kfile);
        assert(s == 1);
    }

    free(strs);
}

int main() {
    kfile = fopen("../kernel.elf","rb");
    assert(kfile != NULL);
    size_t n = fread(&header, sizeof(elf_header), 1, kfile);
    assert(n == 1);

    test_header();
    test_sections();
    test_symtab();

    fclose(kfile);
    return 0;
}
