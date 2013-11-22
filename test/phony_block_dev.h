#ifndef PHONY_BLOCK_DEV_H
#define PHONY_BLOCK_DEV_H
#include <stdint.h>
#include "../fs/block_dev.h"
block_dev_t *init_phony_block(const char *path, const char *mode);
int phony_block_read(uint32_t id, uint32_t pos, void *buf, int count);
int phony_block_write(uint32_t id, uint32_t pos, void *buf, int count);
void phony_block_close();
#endif
