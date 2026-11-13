struct MSG { int cb; int nKind; };
void *PvAllocSwImpl__Fi(struct MSG *pm);
void CopyAb(void *, void *, int) asm("CopyAb__FPvT0Ui");
void *PvAllocSwCopyImpl__FiPv(struct MSG *pm, void *pvSrc)
{
    struct MSG m = *pm;
    void *p = PvAllocSwImpl__Fi(&m);
    if (p) CopyAb(p, pvSrc, pm->cb);
    return p;
}
