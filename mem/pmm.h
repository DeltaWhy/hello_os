#ifndef PMM_H
#define PMM_H
typedef void * paddr_t;
void init_pmm();
paddr_t pmm_alloc_frames(int n);
void pmm_free_frames(paddr_t addr, int n);
#endif
