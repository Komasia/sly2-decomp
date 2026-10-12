typedef struct { short d; short pad; void *pfn; } VTE;
struct O { char pad[0xC]; VTE *vt; };
struct S { char pad[0x2C0]; long fl; char pad2[0xFD0 - 0x2C8]; struct O *po; };
long func_00207A20(int n);
int func_002040F8(struct S *p);
int func_0020B090(struct S *p)
{
    long m;
    if (p->fl & func_00207A20(0x14))
        return 1;
    m = func_00207A20(0x12) | func_00207A20(0x13) | func_00207A20(0x16);
    if (p->fl & m)
        return 0;
    if (p->po)
        return ((int (*)(void *))p->po->vt[12].pfn)((char *)p->po + p->po->vt[12].d);
    return func_002040F8(p);
}
