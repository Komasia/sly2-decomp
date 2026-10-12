struct VTE { short d; short p; void *pfn; };
struct VT { struct VTE a[9]; };
struct P { char pad[0xC]; struct VT *pvt; };
void func_001FB658(struct P *, int, int);
void func_001FC018(struct P *p, int f)
{
    if (!f) ((void (*)(void *))p->pvt->a[7].pfn)((char *)p + p->pvt->a[7].d);
    else {
        int n = 0x1FF;
        func_001FB658(p, ((int (*)(void *))p->pvt->a[8].pfn)((char *)p + p->pvt->a[8].d) == 2 ? n : 0x3FF, 8);
    }
}
