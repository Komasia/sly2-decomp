struct MSG { int cb; int nKind; };
extern unsigned int s_pvWorldMac;
void func_001AE1C8(int);
void *PvAllocSwImpl__Fi(struct MSG *p)
{
    unsigned int pv;
    if (!p->cb)
        return 0;
    func_001AE1C8(p->cb);
    pv = (s_pvWorldMac + (p->nKind - 1)) & -p->nKind;
    s_pvWorldMac = pv + ((p->cb + 15) & -16);
    return (void*)pv;
}
