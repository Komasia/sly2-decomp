// SLY2_CC: tools/compilers/bundle/ee-gcc2.95.3-136
// SLY2_CFLAGS: -O2 -G0
/* sceCdGetReadPos (libcdvd): bytes transferred so far by the sceCdRead in progress, 0 when no read is running. */
extern int D_002C67A0;      /* N-command in progress (1 = read) */
extern int D_002C7900;      /* read position, updated by the IOP */
int sceCdGetReadPos(void)
{
    if (D_002C67A0 != 1) return 0;
    return *(int *)((unsigned)&D_002C7900 | 0x20000000);   /* uncached */
}
