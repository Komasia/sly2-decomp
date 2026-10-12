struct VTE { short d; short pad; void (*pf)(void *); };
struct O { char pad[0xC]; struct VTE *vt; };
struct S { char pad[0x64]; struct O *po; };
void func_001E5468(struct S *p)
{
    struct O *po = p->po;
    if (po) {
        po->vt[50].pf((char *)po + po->vt[50].d);
        p->po = 0;
    }
}
