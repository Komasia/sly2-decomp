struct VTE { short d; short pad; void (*pfn)(void *, int); };
struct O { char pad[0xC]; struct VTE *vt; };
struct S { struct O *po; };
extern char D_004435F0[];
void func_00227788(void *p);
void func_001A3078(struct S *p)
{
    if (p->po) {
        struct O *o;
        struct VTE *e;
        func_00227788(D_004435F0);
        o = p->po;
        e = &o->vt[49];
        e->pfn((char *)o + e->d, -1);
    }
}
