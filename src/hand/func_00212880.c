struct VE { short d; short pad; void (*pf)(void *, int); };
struct S { char pad[0xC]; struct VE *vt; char pad2[0xBC]; int a[10]; };
void func_00212880(struct S *p, int n, int *src)
{
    int i;
    for (i = 0; i < n && (unsigned)i < 10; i++)
        p->a[i] = src[i];
    p->vt[49].pf((char *)p + p->vt[49].d, -1);
}
