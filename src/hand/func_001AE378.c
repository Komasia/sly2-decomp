/* PvAllocStackClearImpl (0x1AE378, Sly 1 memory.c): a cleared stack-heap block. */
struct MSG { int cb; int cbAlign; };  /* the request: size and alignment */
void *PvAllocStackImpl__Fi(struct MSG *pm);
void s1_memset(void *p, int c, int n) asm("memset");
void *PvAllocStackClearImpl__Fi(struct MSG *pm)
{
    struct MSG m = *pm;
    void *p = PvAllocStackImpl__Fi(&m);
    if (p) s1_memset(p, 0, pm->cb);
    return p;
}
