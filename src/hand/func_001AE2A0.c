struct MSG { int cb; int nKind; };
void *PvAllocSwImpl__Fi(struct MSG *pm);
void s1_memset(void *p, int c, int n) asm("memset");
void *PvAllocSwClearImpl__Fi(struct MSG *pm)
{
    struct MSG m = *pm;
    void *p = PvAllocSwImpl__Fi(&m);
    if (p) s1_memset(p, 0, pm->cb);
    return p;
}
