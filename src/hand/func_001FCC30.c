struct VT { int pad[4]; short d; short p; void (*pfn)(void *); };
struct X { char pad[0xC]; struct VT *pvt; char pad2[0x52 - 0x10]; short s52; };
void func_001FB060(struct X *);
void func_001FB658(struct X *, int, int);
void func_001FCC30(int f, long l)
{
    struct X *px = (struct X *)l;
    if (f) { px->s52 = 0; func_001FB060(px); }
    else func_001FB658(px, 0x1000, 0x1000);
    px->pvt->pfn((char *)px + px->pvt->d);
}
