/* PvAllocSwClearImpl (0x1AE2A0, Sly 1 memory.c): a cleared world-heap block. */
struct MSG { int cb; int cbAlign; };  /* the request: size and alignment */
void *PvAllocSwImpl__Fi(struct MSG *pm);
void s1_memset(void *p, int c, int n) asm("memset");
void *PvAllocSwClearImpl__Fi(struct MSG *pm)
{
    struct MSG m = *pm;
    void *p = PvAllocSwImpl__Fi(&m);
    if (p) s1_memset(p, 0, pm->cb);
    return p;
}
