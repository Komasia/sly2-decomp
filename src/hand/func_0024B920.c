/* libmpeg's heap (_initSeq calls it, src/lib naming it _sceMpegHeapInit; see 0x24B930): the position back to the
 * start mark. */
typedef struct MPEGHEAP {
    /* 0x0 */ unsigned int base;
    /* 0x4 */ unsigned int size;
    /* 0x8 */ unsigned int cur;
    /* 0xc */ unsigned int mark;
} MPEGHEAP;

void func_0024B920(MPEGHEAP *ph)
{
    ph->cur = ph->mark;
}
