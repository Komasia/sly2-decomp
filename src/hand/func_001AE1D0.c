struct MSG { int cb; int nKind; };
extern unsigned int s_pvWorldMac;
void CheckForOutOfMemory(int) asm("CheckForOutOfMemory__Fv");
void *PvAllocSwImpl__Fi(struct MSG *p)
{
    unsigned int pv;
    if (!p->cb)
        return 0;
    CheckForOutOfMemory(p->cb);
    pv = (s_pvWorldMac + (p->nKind - 1)) & -p->nKind;
    s_pvWorldMac = pv + ((p->cb + 15) & -16);
    return (void*)pv;
}
