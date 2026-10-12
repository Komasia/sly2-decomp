struct H { int a; int b; unsigned short c; unsigned short d; int *ap; };
struct S { struct H h; unsigned int cqw; };
void func_001ED278(int *p);
struct S *func_001EAD98(struct S *p, struct H *ph)
{
    int *pn;
    p->h = *ph;
    for (pn = p->h.ap; pn < p->h.ap + p->h.c; pn++)
        func_001ED278(pn);
    p->cqw = (p->h.c * sizeof(int) + 15) >> 4;
    return p;
}
