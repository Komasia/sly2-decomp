struct B { int a[12]; };
struct MK { int a; };
extern int D_003DCF9C, D_003DCF98;
extern int g_pdcGif;
void __4GIFS(struct B *pb);
struct MK *__10STACKSCOPE(struct MK *pm);
void _$_10STACKSCOPE(struct MK *pm, int n);
void AllocSw__4DMASi(struct B *pb, int n);
void AddDmaCnt(struct B *pb) asm("AddDmaCnt__4DMAS");
int func_001ECC28(int a, void *p, struct B *pb);
void AddPrimPack(struct B *pb, int a, int b, int c) asm("AddPrimPack__4GIFSiiUl");
void PackAD(struct B *pb, int a, int b) asm("PackAD__4GIFSll");
void AddPrimEnd(struct B *pb) asm("AddPrimEnd__4GIFS");
void AddDmaEnd(struct B *pb) asm("AddDmaEnd__4DMAS");
void Detach(struct B *pb, int a, int *pn) asm("Detach__4DMASPiPP2QW");
void SendDmaSyncGsFinish(int a, int b) asm("SendDmaSyncGsFinish__FP10sceDmaChanP2QW");
void func_00170730(void *p) {
    struct B b;
    struct MK mk;
    int n;
    __4GIFS(&b);
    __10STACKSCOPE(&mk);
    AllocSw__4DMASi(&b, ((D_003DCF9C * 3 + D_003DCF98) << 3) | 4);
    AddDmaCnt(&b);
    if (func_001ECC28(1, p, &b)) {
        AddPrimPack(&b, 0, 1, 0xE);
        PackAD(&b, 0x3F, 0);
        PackAD(&b, 0x61, 0);
        AddPrimEnd(&b);
        AddDmaEnd(&b);
        Detach(&b, 0, &n);
        SendDmaSyncGsFinish(g_pdcGif, n);
    }
    _$_10STACKSCOPE(&mk, 2);
}
