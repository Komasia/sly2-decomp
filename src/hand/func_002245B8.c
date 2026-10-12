struct VTE { short d; short pad; void (*pf)(void *, int); };
struct S { int a[3]; struct VTE *vt; char pad[0x14C]; int k; };
void func_002245B8(struct S *p)
{
    if (p->k == 11) p->vt[76].pf((char *)p + p->vt[76].d, 5);
    else p->vt[76].pf((char *)p + p->vt[76].d, 3);
}
