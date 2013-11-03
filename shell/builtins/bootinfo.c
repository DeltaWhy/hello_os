#include "globals.h"
#include "shell/shell.h"
#include "mboot.h"
#include "hw/screen.h"

extern mboot_info *boot_info;
void bootinfo(int argv, char **argc) {
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
}
builtin bootinfo_builtin = {&bootinfo, "bootinfo", "Displays system information passed from the bootloader."};
