struct VTE { short d; short p; void (*pfn)(void *); };
struct P { char pad[0xC]; VTE *pvt; float f10; char pad2[0x40 - 0x14]; int n40; float f44; char pad3[0x50 - 0x48]; unsigned short f50; unsigned short n52; };
extern "C" void func_001FB658(P *, int, int);
#define VCALL(p, n) ((p)->pvt[n].pfn((char *)(p) + (p)->pvt[n].d))
#define ICALL(p, n) (((int (*)(void *))(p)->pvt[n].pfn)((char *)(p) + (p)->pvt[n].d))
struct Lock {
    P *p;
    Lock(P *pp) { p = pp; VCALL(p, 1); }
    ~Lock() { VCALL(p, 2); }
};
extern "C" void func_001FB8E0(P *p)
{
    Lock l(p);
    unsigned short fl;
    if (p->f50 & 0x200) VCALL(p, 16);
    else p->f44 = p->f10;
    fl = p->f50;
    if (fl & 1) {
        VCALL(p, 9);
        if (ICALL(p, 8) == 1) func_001FB658(p, 0x400, 0x400);
    } else if (p->n40) {
        if (fl & 8) {
            VCALL(p, 10);
            p->n40 = 0;
            func_001FB658(p, 0x1DFF, 0);
        } else {
            if (fl & 0x1C00) VCALL(p, 14);
            if (p->n52) return;
            if (p->f50 & 0x1F0) {
                VCALL(p, 13);
                func_001FB658(p, 0x1F0, 0);
            }
            fl = p->f50;
            if (fl & 2) {
                VCALL(p, 11);
                func_001FB658(p, 2, 0);
            } else if (fl & 4) {
                VCALL(p, 12);
                func_001FB658(p, 4, 0);
            }
        }
    } else if (!p->n52 && !(fl & 0x200)) {
        func_001FB658(p, 0x1FFF, 0);
    }
}
