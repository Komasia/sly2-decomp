struct VTE { short d; short pad; void (*pfn)(); };
struct O { char pad[0xC]; struct VTE *vt; };
struct E { struct O *po; int pad[3]; };
struct P { char pad[0x30C]; int c; int pad2; struct E ae[1]; };
void func_0014D650(struct P *p)
{
    int i;
    for (i = 0; i < p->c; i++) {
        struct O *o = p->ae[i].po;
        struct VTE *e = &o->vt[7];
        ((void (*)(void *))e->pfn)((char *)o + e->d);
    }
    *(int *)((char *)p + 0x620) = 0;
    *(float *)((char *)p + 0x624) = 10.0f;
}
