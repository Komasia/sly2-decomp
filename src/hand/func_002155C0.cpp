extern "C" {
void __10STACKSCOPE(void *p);
void _$_10STACKSCOPE(void *p, int n);
struct X { char pad[0x14]; unsigned long *px14; };
X *func_001EC880(int);
void __4GIFS(void *);
void AllocSw(void *, int) asm("AllocSw__4DMASi");
void AddPrimPack(void *, int, int, int) asm("AddPrimPack__4GIFSiiUl");
void PackAD(void *, int, unsigned long) asm("PackAD__4GIFSll");
void AddPrimEnd(void *) asm("AddPrimEnd__4GIFS");
void DetachCopySw(void *, int, int *, int, int *) asm("DetachCopySw__4DMASPiPP2QWT2i");
}
class FRAME { public: FRAME() { __10STACKSCOPE(this); } ~FRAME() { _$_10STACKSCOPE(this, 2); } };
struct BUF { int a[12]; };
struct P { char pad[0xC4]; int xC4; };
struct Q { int x0; int x4; char pad8[8]; int x10; char pad14[8]; int x1C; int x20; };
extern "C" void func_002155C0(P *p, Q *q);
void func_002155C0(P *p, Q *q)
{
    FRAME frame;
    if (q->x4 == 7) {
        q->x1C = 0;
        q->x20 = 0;
        X *x = func_001EC880(q->x10);
        if (x) {
            BUF b;
            __4GIFS(&b);
            AllocSw(&b, 0x10);
            AddPrimPack(&b, 0, 1, 0xE);
            PackAD(&b, 6, *x->px14);
            PackAD(&b, 0x14, 0x60);
            PackAD(&b, 8, 5);
            AddPrimEnd(&b);
            DetachCopySw(&b, p->xC4, &q->x1C, 0, &q->x20);
        }
    }
}
