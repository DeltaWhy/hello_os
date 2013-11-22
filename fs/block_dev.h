#ifndef BLOCK_DEV_H
#define BLOCK_DEV_H
#include <stdint.h>
typedef int(*block_io_fn)(uint32_t, uint32_t, void *, int);
typedef struct block_dev {
    uint32_t id;
    char *name;
    block_io_fn read;
    block_io_fn write;
} block_dev_t;
#endif
