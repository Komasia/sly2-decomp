/* PvAllocSwImpl (0x1AE1D0, Sly 1 memory.c): a block from the world heap (bump allocated, never freed until FreeSw):
 * the size rounded up to 16 at the requested alignment; 0 for a size of 0. */
struct MSG { int cb; int cbAlign; };  /* the request: size and alignment */
extern unsigned int s_pvWorldMac;
void CheckForOutOfMemory(int) asm("CheckForOutOfMemory__Fv");
void *PvAllocSwImpl__Fi(struct MSG *p)
{
    unsigned int pv;
    if (!p->cb)
        return 0;
    CheckForOutOfMemory(p->cb);
    pv = (s_pvWorldMac + (p->cbAlign - 1)) & -p->cbAlign;
    s_pvWorldMac = pv + ((p->cb + 15) & -16);
    return (void*)pv;
}
