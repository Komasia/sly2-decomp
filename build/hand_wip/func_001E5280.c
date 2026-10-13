struct VTE { short d; short pad; void (*pfn)(void *, int, int); };
struct O { int pad[3]; struct VTE *vt; };
struct P { char pad[0xA4]; int c; struct O *apo[4]; };
int func_00132B10(void *p, int cid);
void *func_002332B8(void *pdst, const void *psrc, int cb);
void func_001E5280(struct P *p, struct O *po, int a, int b)
{
    register int i __asm__("$6");
    if (!func_00132B10(po, 0x33)) return;
    for (i = 0; i < p->c; i++)
        if (p->apo[i] == po) break;
    if (i >= p->c) return;
    {
        register unsigned int addr __asm__("$5") = ((unsigned int)i<<2)+(unsigned int)p;
        unsigned int dest;
        __asm__("daddu %0,%1,$zero":"=r"(dest):"r"(addr));
        func_002332B8((void *)(dest+0xA8),(void *)(addr+0xAC),(p->c-i)*4-4);
    }
    p->c--;
    po->vt[0x54].pfn((char *)po + po->vt[0x54].d, a, b);
}
