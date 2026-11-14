/* libmpeg's heap (sceMpegCreate / _initSeq call it, src/lib naming it _sceMpegHeapAlloc): size bytes at the next
 * multiple of align; past the heap's end an error (_sceMpegError) and 0. */
typedef struct MPEGHEAP {
    /* 0x0 */ unsigned int base;
    /* 0x4 */ unsigned int size;
    /* 0x8 */ unsigned int cur;
    /* 0xc */ unsigned int mark;
} MPEGHEAP;

extern char D_002AC418[];   /* the error message */
void _sceMpegError(void *mp, const char *sz);

unsigned int func_0024B930(void *mp, MPEGHEAP *ph, int cb, unsigned int cbAlign)
{
    unsigned int pv = ((ph->cur + cbAlign - 1) / cbAlign) * cbAlign;
    unsigned int pvEnd = pv + cb;

    if (ph->base + ph->size < pvEnd) {
        _sceMpegError(mp, D_002AC418);
        return 0;
    }
    ph->cur = pvEnd;
    return pv;
}
