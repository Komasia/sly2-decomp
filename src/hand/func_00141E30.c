struct VTE { short d; short pad; void (*pfn)(); };
struct O { char pad[0xC]; struct VTE *vt; };
void func_00141E30(struct O *p)
{
    struct VTE *e = &p->vt[3];
    ((void (*)(void *, int, int, int, int, int))e->pfn)((char *)p + e->d, 0x1A, 0, 0, 0, 0);
}
