struct VE { short d; short pad; void (*pf)(void *, int); };
struct S { char pad[0xC]; struct VE *vt; char pad2[0x6C]; int x7c; char pad3[4]; void *x84; char pad4[0x24]; int xac; };
void func_00217BA0(void *p);
void func_00214300(struct S *p, int a);
void func_00213830(struct S *p, int a)
{
    func_00217BA0(p->x84);
    p->vt[21].pf((char *)p + p->vt[21].d, 1);
    if (p->xac)
        func_00214300(p, 0);
    p->x7c = a;
}
