struct VE { short d; short pad; void (*pfn)(); };
struct O { char pad[0xC]; struct VE *vt; };
struct L { char pad[0x20]; int x20; };
struct S { char pad[0xC]; struct VE *vt; char pad1[0xE0 - 0x10]; int c; struct O *ao[4]; int af[4]; char pad2[0x128 - 0x104]; struct L *x128; };
#define VCALL(o, n, args...) ((void (*)())(o)->vt[n].pfn)((char *)(o) + (o)->vt[n].d, args)
#define VCALL0(o, n) ((void (*)())(o)->vt[n].pfn)((char *)(o) + (o)->vt[n].d)
void func_001BED18(struct S *p)
{
    int i;
    if (!p->x128) return;
    p->x128->x20 = 0;
    p->x128 = 0;
    for (i = 0; i < p->c; i++) {
        struct O *o = p->ao[i];
        if (p->af[i] & 1) VCALL0(o, 9);
        if (p->af[i] & 2) VCALL(o, 21, 1);
    }
    VCALL(p, 21, 0);
    VCALL(p, 3, 3, 0, 0, 0, 0);
}
