#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "../fs/block_dev.h"
#include "phony_block_dev.h"

static block_dev_t phony_block;
static FILE *file;

block_dev_t *init_phony_block(const char *path, const char *mode) {
    // this will only work for one device instance
    phony_block.id = 0;
    phony_block.name = "phony0";
    file = fopen(path, mode);
    if (file == NULL) {
        fprintf(stderr, "error initializing phony_block_dev: %s\n", strerror(errno));
        exit(-1);
    }
    phony_block.read = &phony_block_read;
    phony_block.write = &phony_block_write;

    return &phony_block;
}
    
int phony_block_read(uint32_t id, uint32_t pos, char *buf, int count) {
    ((void)id);
    if (fseek(file, pos, SEEK_SET) != 0) {
        fprintf(stderr, "error reading phony_block_dev: %s\n", strerror(errno));
        exit(-1);
    }
    return (int)fread(buf, 1, count, file);
}

int phony_block_write(uint32_t id, uint32_t pos, char *buf, int count) {
    ((void)id);
    if (fseek(file, pos, SEEK_SET) != 0) {
        fprintf(stderr, "error writing phony_block_dev: %s\n", strerror(errno));
        exit(-1);
    }
    return (int)fwrite(buf, 1, count, file);
}

void phony_block_close() {
    if (file != NULL) {
        if (fclose(file) != 0) {
            fprintf(stderr, "error closing phony_block_dev: %s\n", strerror(errno));
            exit(-1);
        }
    }
}
