#ifndef FS_H
#define FS_H
#include <stdint.h>
#include <stdbool.h>
#include "fs/block_dev.h"

#define MAX_FILESYSTEMS 32

typedef int(*file_io_fn)(char *, uint64_t);

enum FILE_FLAGS {
    FILE_FLAG_READ = 0x1,
    FILE_FLAG_WRITE = 0x2,
    FILE_FLAG_APPEND = 0x4,
    FILE_FLAG_CREATE = 0x8,
    FILE_FLAG_TRUNCATE = 0x10
};

typedef struct file {
    char *path;
    uint64_t position;
    uint32_t flags;
    file_io_fn read;
    file_io_fn write;
} file_t;

enum FILE_ATTRS {
    FILE_ATTR_READONLY = 0x1,
    FILE_ATTR_HIDDEN = 0x2,
    FILE_ATTR_DIRECTORY = 0x4
};

typedef struct dir_entry {
    char *name;
    uint32_t attributes;
    uint64_t size;
} dir_entry_t;

typedef dir_entry_t *(*dir_next_fn)();
typedef struct dir {
    char *path;
    uint32_t position;
    dir_next_fn next;
} dir_t;

typedef file_t *(*fs_fopen_fn)(char *, uint32_t);
typedef dir_t *(*fs_diropen_fn)(char *);
typedef struct file_system {
    uint32_t id;
    block_dev_t *device;
    char * type;
    char * label;
    fs_fopen_fn open_file;
    fs_diropen_fn open_dir;
} file_system_t;

file_system_t * fs_mount(block_dev_t *device);
bool fs_unmount(file_system_t *fs);
#endif
