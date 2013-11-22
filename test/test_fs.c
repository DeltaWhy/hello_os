#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "phony_block_dev.h"
#include "../fs/block_dev.h"
#include "../fs/fs.h"

void test_phony_block() {
    // does our phony block device work as expected?
    system("cp test_floppy.img test_floppy1.img");

    block_dev_t *phony0 = init_phony_block("test_floppy1.img", "r+");

    char buf[1024];
    assert(phony0->read(phony0->id, 0, buf, 1024) == 1024);
    assert(memcmp(buf+3, "mkfs.fat", 7) == 0);

    assert(phony0->read(phony0->id, 0x2b, buf, 1024) == 1024);
    assert(memcmp(buf, "NO NAME", 7) == 0);

    strcpy(buf, "TESTFLOP");
    assert(phony0->write(phony0->id, 0x2b, buf, 8) == 8);

    assert(phony0->read(phony0->id, 0, buf, 1024) == 1024);
    assert(memcmp(buf+0x2b, "TESTFLOP", 8) == 0);

    phony_block_close();
    system("rm test_floppy1.img");
}

void test_fat() {
    system("cp test_floppy.img test_floppy2.img");

    block_dev_t *phony0 = init_phony_block("test_floppy2.img", "r+");
    file_system_t *fs = fs_mount(phony0);

    assert(fs != NULL);

    assert(fs_unmount(fs));
    phony_block_close();
    system("rm test_floppy2.img");
}

int main() {
    test_phony_block();
    test_fat();

    return 0;
}
