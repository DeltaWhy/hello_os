#include <stddef.h>
#include "globals.h"
#include "hw/screen.h"
#include "fs/block_dev.h"
#include "fs/fs.h"
#include "fs/fat.h"
#include "string.h"

file_system_t filesystems[MAX_FILESYSTEMS];
uint32_t fs_count = 0;

file_system_t * fs_mount(block_dev_t *device) {
    filesystems[fs_count].id = fs_count;
    filesystems[fs_count].device = device;
    filesystems[fs_count].type = NULL;
    filesystems[fs_count].label = NULL;
    fs_count++;
    // TODO - check the filesystem type
    fat_mount(&filesystems[fs_count-1]);
    return &filesystems[fs_count-1];
}

bool fs_unmount(file_system_t *fs) {
    if (fs->id >= fs_count) {
        printf("Tried to unmount non-mounted filesystem\n");
        return false;
    }
    // TODO - check the filesystem type
    if (!fat_unmount(fs)) return false;
    memset(fs, 0, sizeof(file_system_t));
    return true;
}
