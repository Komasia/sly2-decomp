struct RGBA2 { unsigned char r, g, b, a; };
struct RGBA {
    unsigned char r, g, b, a;
    RGBA(const RGBA &c) { *(RGBA2 *)this = *(const RGBA2 *)&c; }
} __attribute__((aligned(16)));
struct L { char pad[0x84]; char *pb; };
struct S { int x0; int k; L *pl; int xc; int i; void *x14; };
struct T { char pad[0x30]; S *x30; char pad34[0x24]; int x58; };
extern "C" int func_00217EF8(void *p);
extern "C" void func_00217CA8(void *p, int k, int z, void *q, RGBA c0, RGBA c1);
extern "C" void *func_001BEED8(int);
extern "C" void *func_001BEB28(void *);
extern "C" void func_00215730(S *p, T *t, void *q, RGBA c0, RGBA c1)
{
    t->x30 = p;
    switch (p->k) {
    case 4:
        t->x58 = func_00217EF8(p->pl->pb + p->i * 0x30);
        func_00217CA8(p->pl->pb + p->i * 0x30, 0x314, t->x58, q, c0, c1);
        break;
    case 6:
        if (p->i != -1) {
            void *pv = func_001BEED8(p->i);
            if (pv)
                p->x14 = func_001BEB28(pv);
        }
        break;
    }
}
