struct VT { int pad[4]; short d; short p; void (*pfn)(void *); };
struct X { char pad[0xC]; struct VT *pvt; };
struct DL;
extern struct DL D_003DD08C;
int func_0011A380(struct DL *, void *);
void func_0011A2E8(struct DL *, void *);
void func_001FB710(struct X *px)
{
    if (func_0011A380(&D_003DD08C, px)) {
        func_0011A2E8(&D_003DD08C, px);
        px->pvt->pfn((char *)px + px->pvt->d);
    }
}
