struct MSG { int cb; int nKind; };
extern unsigned int D_002F6384;
void func_001AE1C8(int);
void *func_001AE1D0(struct MSG *p)
{
    unsigned int pv;
    if (!p->cb)
        return 0;
    func_001AE1C8(p->cb);
    pv = (D_002F6384 + (p->nKind - 1)) & -p->nKind;
    D_002F6384 = pv + ((p->cb + 15) & -16);
    return (void*)pv;
}
