struct VTE { short d; short pad; void (*pfn)(); };
struct S { char pad[0x20]; struct VTE *vt; };
void func_00182CD8(struct S *p, int a, float *pg, int b, int c)
{
    float g;
    struct VTE *e;
    e = &p->vt[2];
    ((void (*)(void *, int, float *))e->pfn)((char *)p + e->d, a, &g);
    e = &p->vt[3];
    ((void (*)(void *, int, int, int, float))e->pfn)((char *)p + e->d, a, b, c, g);
    if (pg) *pg = g;
}
