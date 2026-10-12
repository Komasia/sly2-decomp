struct VTE { short d; short pad; void (*pfn)(void *); };
struct A { char pad[0xC]; struct VTE *vt; };
void func_001FB098(struct A *p, float g);
void func_001FB658(struct A *p, int a, int b);
void func_001FBB30(int f, long l)
{
    struct A *p = (struct A *)l;
    if (!f)
        func_001FB098(p, 0.0f);
    else
        func_001FB658(p, 0x400, 0x400);
    p->vt[2].pfn((char *)p + p->vt[2].d);
}
