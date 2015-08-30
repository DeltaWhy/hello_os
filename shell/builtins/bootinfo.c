#include "globals.h"
#include "shell/shell.h"
#include "mboot.h"
#include "hw/screen.h"

extern mboot_info *boot_info;
static void bootinfo(int argv, char **argc) {
    UNUSED(argv);
    UNUSED(argc);

    printf("Multiboot flags: %#x\n", boot_info->flags);
    printf("Low memory: %uK", boot_info->mem_lo);
    printf("    High memory: %uK\n", boot_info->mem_hi);
    printf("Kernel command line: %s\n", boot_info->cmd_line);
    printf("Bootloader name: %s\n", boot_info->bootloader_name);
    printf("Memory map:\n");
    mboot_mmap_entry *e = boot_info->mmap_addr;
    while (((uint32_t)e) < ((uint32_t)boot_info->mmap_addr) + boot_info->mmap_length) {
        printf("    %p\n", e);
        printf("    Entry size=%d base=0x%.x%.8x\n", e->size, e->addr_hi, e->addr_lo);
        printf("        length=0x%.x%x type=%#x\n", e->len_hi, e->len_lo, e->type);
        e = (mboot_mmap_entry *)((uint32_t)e + e->size + 4);
    }
    printf("Module count: %d, address: %p\n", boot_info->mods_count, boot_info->mods_addr);
    for (unsigned int i=0; i < boot_info->mods_count; i++) {
        mboot_module m = boot_info->mods_addr[i];
        printf("Module:\n");
        printf("    start=%p end=%p\n", m.mod_start, m.mod_end);
    }
    if (boot_info->flags & 0x20) {
        printf("ELF section table:\n");
        printf("    num=%d size=%d addr=%p shndx=%p\n", boot_info->elf_section_num, boot_info->elf_section_size, boot_info->elf_section_addr, boot_info->elf_section_shndx);
    }
}
builtin bootinfo_builtin = {&bootinfo, "bootinfo", "Displays system information passed from the bootloader."};
