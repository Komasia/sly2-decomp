typedef unsigned long ulong;
typedef unsigned int uint;
struct QW { int a[4]; };
class GIFS {
public:
    int a[10];
    GIFS();
    void AllocStatic(int cqw, QW *aqw);
    void AddPrimPack(int prim, int creg, ulong regs);
    void PackXYZ(int x, int y, int z);
    void PackAD(long a, long d);
    void AddPrimEnd();
    void Detach(int *pcqw, QW **paqw, QW **paqwCopy);
};
struct TEX0 {
    ulong tbp0 : 14;
    ulong tbw : 6;
    ulong psm : 6;
    ulong tw : 4;
    ulong th : 4;
    ulong tcc : 1;
    ulong tfx : 2;
    ulong cbp : 14;
    ulong cpsm : 4;
    ulong csm : 1;
    ulong csa : 5;
    ulong cld : 3;
};
struct T {
    int dx, dy;
    TEX0 tex0;
    int c10;
    QW *a14;
    int c18;
    QW *a1C;
};
struct X { int x0, x4, x8; };
extern "C" {
int func_00170548(X *px, int cb);
int func_001703C0(int n);
}

extern "C" void func_001BE398(T *pt, X *px)
{
    int cbBlock = 0x40;
    pt->dx = 0x80;
    pt->dy = 0x80;
    int tbw = pt->dx / cbBlock;
    int tbp = func_00170548(px, 0x100);
    pt->tex0.tbp0 = tbp;
    pt->tex0.tbw = tbw;
    pt->tex0.psm = 0;
    tbp >>= 5;
    pt->tex0.tw = func_001703C0(pt->dx);
    pt->tex0.th = func_001703C0(pt->dy);
    pt->tex0.tcc = 1;
    int zbp = (px->x8 - 0x100) >> 5;
    GIFS gifs;
    int xOff = 0x800 - pt->dx / 2;
    int yOff = 0x800 - pt->dy / 2;
    QW aqw[0x40];
    gifs.AllocStatic(0x40, aqw);
    gifs.AddPrimPack(0, 1, 0xE);
    int w = pt->dx;
    int m = cbBlock;
    if (cbBlock < w) m = w;
    gifs.PackAD(0x4C, tbp | ((ulong)(m / 0x40) << 16));
    gifs.PackAD(0x4E, zbp | 0x30000000);
    gifs.PackAD(0x18, (xOff << 4) | ((ulong)(yOff << 4) << 32));
    gifs.PackAD(0x40, ((ulong)(pt->dx - 1) << 16) | ((ulong)(pt->dy - 1) << 48));
    gifs.PackAD(0x47, 0x30000);
    gifs.PackAD(1, 0);
    gifs.AddPrimPack(6, 1, 5);
    int x = xOff;
    while (x < xOff + pt->dx) {
        gifs.PackXYZ(x << 4, yOff << 4, 0);
        x += 0x20;
        gifs.PackXYZ(x << 4, (yOff + pt->dy) << 4, 0);
    }
    gifs.AddPrimEnd();
    gifs.Detach(&pt->c10, 0, &pt->a14);
    gifs.AllocStatic(0x40, aqw);
    gifs.AddPrimPack(0, 1, 0xE);
    gifs.PackAD(6, *(long *)&pt->tex0);
    gifs.PackAD(0x14, 0x60);
    gifs.PackAD(8, 5);
    gifs.AddPrimEnd();
    gifs.Detach(&pt->c18, 0, &pt->a1C);
}
