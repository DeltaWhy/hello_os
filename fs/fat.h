#ifndef FAT_H
#define FAT_H
#include <stdint.h>
#include <stdbool.h>
typedef struct __attribute__ ((__packed__)) fat16_ebpb {
    uint8_t drive_num;
    uint8_t nt_flags;
    uint8_t signature;
    uint32_t vol_serial;
    char vol_label[11]; //padded with spaces
    char system_id[8]; //padded with spaces
    char ignore[448];
    uint16_t boot_sig;
} fat16_ebpb_t;

typedef struct __attribute__ ((__packed__)) fat32_ebpb {
    uint32_t sectors_per_fat;
    uint16_t flags;
    uint16_t version;
    uint32_t root_dir_cluster;
    char reserved[12];
    uint8_t drive_num;
    uint8_t nt_flags;
    uint8_t signature;
    uint32_t vol_serial;
    char vol_label[11];
    char system_id[8];
    char ignore[420];
    uint16_t boot_sig;
} fat32_ebpb_t;

typedef struct __attribute__ ((__packed__)) fat_bpb {
    char ignore[3];
    char oem[8];
    uint16_t bytes_per_sector;
    uint8_t sectors_per_cluster;
    uint16_t reserved_sectors;
    uint8_t num_fats;
    uint16_t num_direntries;
    uint16_t total_sectors;
    uint8_t media_descriptor;
    uint16_t sectors_per_fat; //fat12 and 16 only
    uint16_t sectors_per_track;
    uint16_t num_heads;
    uint32_t num_hidden_sectors;
    uint32_t total_sectors_large;
    union {
        struct fat16_ebpb fat16_ebpb;
        struct fat32_ebpb fat32_ebpb;
    };
} fat_bpb_t;

typedef struct __attribute__ ((__packed__)) fat_dir_entry {
    char filename[11];
    uint8_t attributes;
    uint8_t reserved;
    uint8_t created_time_tenths;
    uint16_t created_time; //hour 5 bits, minute 6 bits, second 5 bits
    uint16_t created_date; //year 7 bits, month 4 bits, day 5 bits
    uint16_t accessed_date;
    uint16_t first_cluster_hi;
    uint16_t modified_time;
    uint16_t modified_date;
    uint16_t first_cluster_lo;
    uint32_t size;
} fat_dir_entry_t;

typedef struct __attribute__ ((__packed__)) fat_lfn_entry {
    uint8_t order;
    uint16_t filename1[5];
    uint8_t attributes;
    uint8_t long_entry_type;
    uint8_t checksum;
    uint16_t filename2[6];
    uint16_t zero;
    uint16_t filename3[2];
} fat_lfn_entry_t;

enum FAT_TYPE { FAT12_TYPE, FAT16_TYPE, FAT32_TYPE };
typedef struct fat_info {
    enum FAT_TYPE type;
    fat_bpb_t bpb;
    void * fat;
    fat_dir_entry_t * root_dir;
} fat_info_t;

bool fat_mount(file_system_t *fs);
bool fat_unmount(file_system_t *fs);
#endif
