/* libmpeg's heap (sceMpegCreate calls it; see 0x24B930): the start mark (+0xC) set to the current position (+0x8). */
typedef struct MPEGHEAP {
    /* 0x0 */ unsigned int base;
    /* 0x4 */ unsigned int size;
    /* 0x8 */ unsigned int cur;
    /* 0xc */ unsigned int mark;
} MPEGHEAP;

void func_0024B910(MPEGHEAP *ph)
{
    ph->mark = ph->cur;
}
