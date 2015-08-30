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
    if (boot_info->flags & MBOOT_FLAG_CMDLINE) printf("Kernel command line: %s\n", boot_info->cmd_line);
    printf("Bootloader name: %s\n", boot_info->bootloader_name);
    printf("Memory map:\n");
    mboot_mmap_entry *e = boot_info->mmap_addr;
    while (((uint32_t)e) < ((uint32_t)boot_info->mmap_addr) + boot_info->mmap_length) {
        printf("    %p\n", e);
        printf("    Entry size=%d base=0x%.x%.8x\n", e->size, e->addr_hi, e->addr_lo);
        printf("        length=0x%.x%x type=%#x\n", e->len_hi, e->len_lo, e->type);
        e = (mboot_mmap_entry *)((uint32_t)e + e->size + 4);
    }
    /*printf("Module count: %d, address: %p\n", boot_info->mods_count, boot_info->mods_addr);
    for (unsigned int i=0; i < boot_info->mods_count; i++) {
        mboot_module m = boot_info->mods_addr[i];
        printf("Module:\n");
        printf("    start=%p end=%p\n", m.mod_start, m.mod_end);
    }
    if (boot_info->flags & MBOOT_FLAG_ELF_SHDR) {
        printf("ELF section table:\n");
        printf("    num=%d size=%d addr=%p shndx=%p\n", boot_info->elf_section_num, boot_info->elf_section_size, boot_info->elf_section_addr, boot_info->elf_section_shndx);
    }*/
    if (boot_info->flags & MBOOT_FLAG_APM_TABLE) {
        printf("APM table:\n");
        printf("   version=%d cseg=%x offset=%x flags=%x cseg_len=%x\n", boot_info->apm_table->version, boot_info->apm_table->cseg, boot_info->apm_table->offset, boot_info->apm_table->flags, boot_info->apm_table->cseg_len);
        printf("    cseg_16=%x cseg_16_len=%x dseg_16=%x dseg_16_len=%x\n", boot_info->apm_table->cseg_16, boot_info->apm_table->cseg_16_len, boot_info->apm_table->dseg_16, boot_info->apm_table->dseg_16_len);
    }
}
builtin bootinfo_builtin = {&bootinfo, "bootinfo", "Displays system information passed from the bootloader."};
