struct S { char pad[0xC4]; void *xC4; };
extern int D_002C40A4;
int func_00117C20(void *a);
int PvAllocClear__FP4HEAPii(void *heap, int cb, int k);
void func_002149D8(struct S *p, void *a, void *b, int n, int m);
void func_00214398(struct S *p, void *a, void *b, int *pn, int *pm)
{
    int i;
    *pn = func_00117C20(a);
    *pm = PvAllocClear__FP4HEAPii(p->xC4, (*pn + 1) << 6, D_002C40A4 ? 0x13 : 0x11);
    for (i = 1; i <= *pn; i++)
        func_002149D8(p, a, b, *pn, *pm);
}
