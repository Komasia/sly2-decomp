typedef unsigned long ulong;
struct G;
extern struct G D_003DD490;
void func_00147E88(struct G *g, void *p);
struct S { char pad[0x10]; int x10; void *x14; char pad2[0x10]; ulong fl; int pad3[2]; float x38; };
void func_001A6C48(struct S *p, float g)
{
    p->x38 = g;
    if (!p->x10 && ((int)(p->fl >> 60) & 1)) func_00147E88(&D_003DD490, p->x14);
}
