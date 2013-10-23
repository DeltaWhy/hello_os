#include "globals.h"
#include "shell/shell.h"
#include "mboot.h"
#include "hw/screen.h"

extern mboot_info *boot_info;
void bootinfo(int argv, char **argc) {
    UNUSED(argv);
    UNUSED(argc);

    char tmp[64];
    print("Multiboot flags: 0x");
    itoa(boot_info->flags, tmp, 16);
    print(tmp);
    print("\nLow memory: ");
    itoa(boot_info->mem_lo, tmp, 10);
    print(tmp);
    print("K    High memory: ");
    itoa(boot_info->mem_hi, tmp, 10);
    print(tmp);
    print("K\nKernel command line: ");
    print(boot_info->cmd_line);
    print("\nBootloader name: ");
    print(boot_info->bootloader_name);
    print("\nMemory map:\n");
    mboot_mmap_entry *e = boot_info->mmap_addr;
    while (((uint32_t)e) < ((uint32_t)boot_info->mmap_addr) + boot_info->mmap_length) {
        print("    0x");
        itoa((uint32_t)e, tmp, 16);
        print(tmp);
        print("\n    Entry size=");
        itoa(e->size, tmp, 10);
        print(tmp);
        print(" base=0x");
        itoa(e->addr_hi, tmp, 16);
        print(tmp);
        itoa(e->addr_lo, tmp, 16);
        print(tmp);
        print("\n        length=0x");
        itoa(e->len_hi, tmp, 16);
        print(tmp);
        itoa(e->len_lo, tmp, 16);
        print(tmp);
        print(" type: 0x");
        itoa(e->type, tmp, 16);
        print(tmp);
        print("\n");
        e = (mboot_mmap_entry *)((uint32_t)e + e->size + 4);
    }
}
builtin bootinfo_builtin = {&bootinfo, "bootinfo", "Displays system information passed from the bootloader."};
