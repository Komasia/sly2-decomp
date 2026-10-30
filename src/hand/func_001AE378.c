struct MSG { int cb; int nKind; };
void *PvAllocSlot__FP8ALLOCREQ(struct MSG *pm);
void func_002333B4(void *p, int c, int n);
void *func_001AE378(struct MSG *pm)
{
    struct MSG m = *pm;
    void *p = PvAllocSlot__FP8ALLOCREQ(&m);
    if (p) func_002333B4(p, 0, pm->cb);
    return p;
}
