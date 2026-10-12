struct MSG { int cb; int nKind; };
void *func_001AE1D0(struct MSG *pm);
void func_001AE5A0(void *, void *, int);
void *func_001AE238(struct MSG *pm, void *pvSrc)
{
    struct MSG m = *pm;
    void *p = func_001AE1D0(&m);
    if (p) func_001AE5A0(p, pvSrc, pm->cb);
    return p;
}
