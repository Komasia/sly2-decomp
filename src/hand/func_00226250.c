struct VTE { short d; short pad; void (*pf)(); };
struct S { int a[3]; struct VTE *vt; char pad[0x140]; void *x; char pad2[0x6C]; void *y; void *z; void *w; };
int func_001C4700(void *x, int a);
void *func_001CB250(void *y, int a);
void func_001D6B00(void *z, void *v);
void func_00226250(struct S *p)
{
    if (p->x && func_001C4700(p->x, 0xFF)) {
        if (p->y) {
            void *v = func_001CB250(p->y, 0);
            if (!v) return;
            p->w = v;
            if (p->z) func_001D6B00(p->z, v);
            p->vt[3].pf((char *)p + p->vt[3].d, 5, 0, 0, 0, 0);
        } else
            p->vt[3].pf((char *)p + p->vt[3].d, 5, 0, 0, 0, 0);
    }
}
