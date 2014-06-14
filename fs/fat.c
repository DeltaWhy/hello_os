#include "globals.h"
#include "hw/screen.h"
#include "fs/fs.h"
#include "fs/fat.h"
#include "string.h"
#include "malloc.h"

fat_info_t fat_infos[MAX_FILESYSTEMS];

bool fat_mount(file_system_t *fs) {
    fs->device->read(fs->device->id, 0, &fat_infos[fs->id].bpb, sizeof(fat_bpb_t));

    int total_clusters = fat_infos[fs->id].bpb.total_sectors / fat_infos[fs->id].bpb.sectors_per_cluster;
    if (total_clusters < 4085) {
        fat_infos[fs->id].type = FAT12_TYPE;
    } else if (total_clusters < 65525) {
        fat_infos[fs->id].type = FAT16_TYPE;
    } else {
        fat_infos[fs->id].type = FAT32_TYPE;
    }

    uint8_t signature;
    size_t fat_size;
    switch (fat_infos[fs->id].type) {
        case FAT12_TYPE:
        case FAT16_TYPE:
            signature = fat_infos[fs->id].bpb.fat16_ebpb.signature;
            fat_size = fat_infos[fs->id].bpb.bytes_per_sector * fat_infos[fs->id].bpb.sectors_per_fat;
            break;
        case FAT32_TYPE:
            signature = fat_infos[fs->id].bpb.fat32_ebpb.signature;
            fat_size = fat_infos[fs->id].bpb.bytes_per_sector * fat_infos[fs->id].bpb.fat32_ebpb.sectors_per_fat;
            break;
    }
    if (signature != 0x28 && signature != 0x29) {
        printf("FAT signature not found\n");
        return false;
    }
    if (fat_infos[fs->id].type != FAT12_TYPE) {
        printf("FAT type not implemented\n");
        return false;
    }

    // TODO - load FAT and root dir
    fat_infos[fs->id].fat = malloc(fat_size);
    fs->device->read(fs->device->id, 512, fat_infos[fs->id].fat, fat_size);
    uint32_t root_dir_start = 512 + fat_size*fat_infos[fs->id].bpb.num_fats;
    fat_infos[fs->id].root_dir = malloc(fat_infos[fs->id].bpb.num_direntries*sizeof(fat_dir_entry_t));
    fs->device->read(fs->device->id, root_dir_start, fat_infos[fs->id].root_dir, fat_infos[fs->id].bpb.num_direntries*sizeof(fat_dir_entry_t));
    return true;
}

bool fat_unmount(file_system_t *fs) {
    free(fat_infos[fs->id].fat);

    return true;
}
