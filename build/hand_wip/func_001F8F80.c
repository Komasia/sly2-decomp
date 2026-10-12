typedef unsigned long ulong;
struct H { char pad[0x98]; short h98; };
struct E { char pad[0xA0]; int nA0; char pad2[0xC0 - 0xA4]; int nC0; };
struct O { char pad[0x58]; struct H *p58; struct H *p5C; char pad2[0xE8 - 0x60]; struct E *pe; char pad3[0x148 - 0xEC]; ulong fl; };
struct L { char pad[0x40]; struct L *pNext; char pad2[0x60 - 0x44]; struct O *po; };
struct P { char pad[0x3D1C]; struct L *pl; };
struct A { int b[0x301]; int n; };
int func_00230348(int, struct O *);
void func_001F8E90(struct P *, struct O *, int *, struct A *);
void func_001F9240(struct P *, int, int, struct A *);
void func_001F8F80(struct P *p, int k)
{
    struct A a;
    struct L *pl;
    struct O *po;
    for (pl = p->pl; pl; pl = pl->pNext) {
        struct E *pe;
        po = pl->po;
        pe = po->pe;
        if (!pe) continue;
        if (po->fl & 0x8000000) continue;
        if (pe->nC0 == 3 && pe->nA0 == 3) continue;
        if ((k & 1) && func_00230348(po->p58->h98, po) && func_00230348(po->p5C->h98, po)) continue;
        a.n = 0;
        func_001F8E90(p, po, &a.n, &a);
        func_001F9240(p, k, a.n, &a);
    }
    for (pl = p->pl; pl; pl = pl->pNext) {
        po = pl->po;
        po->fl &= ~0x8000000L;
        po->fl &= ~0x10000000L;
    }
}
