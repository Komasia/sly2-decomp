struct VTE { short d; short p; void (*pfn)(void *); };
struct VT { struct VTE a[8]; };
struct X { char pad[0xC]; struct VT *pvt; char pad2[0x40 - 0x10]; int f40; char pad3[0x50 - 0x44]; unsigned short fl; short s52; };
void func_001FB060(struct X *);
void func_001FB658(struct X *, int, int);
#define VF(q, n) (q)->pvt->a[n].pfn((char *)(q) + (q)->pvt->a[n].d)
void func_001FCBA8(int f, long l)
{
    struct X *px = (struct X *)l;
    px->f40 = f;
    if (f) func_001FB658(px, 0x1000, 0x1000);
    else {
        func_001FB060(px);
        px->s52 = 0;
        if (!(px->fl & 8)) VF(px, 7);
    }
    VF(px, 2);
}
