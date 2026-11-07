struct VTE { short d; short pad; void (*pf)(void *, int); };
struct S { int a[3]; struct VTE *vt; char pad[0x140]; int x; };
// name: SafeHouse port (FAcceptCarryContact)
int FAcceptCarryContact__FP3ALO(struct S *p)
{
    switch (p->x) { case 1: case 2: p->vt[76].pf((char *)p + p->vt[76].d, 3); }
    return 1;
}
