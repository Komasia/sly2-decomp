struct VT { int pad[2]; short d; short p; void (*pfn)(void *); };
struct X { char pad[0xC]; struct VT *pvt; char pad2[0x40 - 0x10]; void *p40; char pad3[0x50 - 0x44]; unsigned short fl; };
void func_001FBB30(void);
void func_00232498(void *, void (*)(void), void *);
void func_001FB658(struct X *, int, int);
void func_001FBFB0(struct X *px)
{
    if (px->fl & 0x400) {
        px->pvt->pfn((char *)px + px->pvt->d);
        func_00232498(px->p40, func_001FBB30, px);
        func_001FB658(px, 0x400, 0);
    }
}
