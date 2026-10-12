typedef unsigned long ulong;
typedef unsigned int uint;
struct QW;
class GIFS {
public:
    int a[10];
    GIFS();
    void AllocStatic(int cqw, void *aqw);
    void AddDmaCnt();
    void AddPrimPack(int prim, int creg, ulong regs);
    void PackUV(int u, int v);
    void PackXYZF(int x, int y, int z, int fog);
    void PackAD(long a, long d);
    void AddPrimEnd();
    void EndDmaCnt();
    void Detach(int *pcqw, QW **paqw);
};
struct RGBA { unsigned char r, g, b, a; };
struct FONT { char pad[0x170]; };
struct TB {
    float x, y, dx, dy;
    int pad10;
    int x14;
    int pad[2];
    void SetPos(float x, float y) __asm__("func_00258438");
    void SetSize(float dx, float dy) __asm__("func_00258448");
    void SetColor(RGBA *prgba) __asm__("func_00258458");
    void SetHorizontalJust(int j) __asm__("func_00258470");
    void SetVerticalJust(int j) __asm__("func_00258478");
};
struct S { int x0; char *x4; };
struct P { char pad[0x104]; S *x104; int pad108[2]; char *x110; int pad114; int x118; int x11C; };
extern "C" {
extern void *D_002DE760;
extern char D_003E1C20[];
void func_0015F078(void *pf, float sx, float sy);
char *func_00210CA8(void *p, char *k);
void func_0015F928(FONT *pfont, char *str, void *pf);
float func_0015FEF8(FONT *pfont, float dx);
float func_0015FF40(FONT *pfont);
void func_001CD5F0(RGBA rgba, GIFS *pgifs, float x0, float y0, float x1, float y1);
void func_0015FFD0(FONT *pfont, TB *ptb, int z, GIFS *pgifs);
void func_0015F0C0(void *pf);
}

extern "C" void func_001B3700(P *p)
{
    GIFS gifs;
    gifs.AllocStatic(0x200, p->x110 + 0x41BC00);
    gifs.AddDmaCnt();
    gifs.AddPrimPack(6, 1, 0xE);
    gifs.PackAD(6, 0xAA8031800L);
    gifs.PackAD(0x14, 0x61);
    gifs.PackAD(8, 5);
    gifs.PackAD(0x42, 0x44);
    gifs.PackAD(0x47, 0x31001);
    gifs.AddPrimPack(0x116, 4, 0x4343);
    gifs.PackUV(8, 8);
    gifs.PackXYZF(0x7000, 0x7900, 0, 0);
    gifs.PackUV((p->x118 << 4) | 8, (p->x11C << 4) | 8);
    gifs.PackXYZF(0x9000, 0x8700, 0, 0);
    gifs.AddPrimPack(0, 1, 0xE);
    gifs.PackAD(0x61, 0);
    gifs.AddPrimEnd();
    gifs.EndDmaCnt();
    gifs.Detach(0, 0);
    if (p->x104) {
        gifs.AllocStatic(0x200, p->x110 + 0x41DC00);
        gifs.AddDmaCnt();
        func_0015F078(D_002DE760, 0.8f, 0.8f);
        FONT font;
        func_0015F928(&font, func_00210CA8(D_003E1C20, p->x104->x4), D_002DE760);
        float dy = func_0015FEF8(&font, 320.0f);
        float dx = func_0015FF40(&font);
        TB tb;
        tb.SetPos(320.0f - dx * 0.5f, 476.8f - dy);
        tb.SetSize(dx, dy);
        RGBA rgba;
        *(uint *)&rgba = 0xFFC0C0C0;
        tb.SetColor(&rgba);
        tb.SetHorizontalJust(0);
        tb.SetVerticalJust(0);
        tb.x14 = 1;
        *(uint *)&rgba = 0x80000000;
        func_001CD5F0(rgba, &gifs, tb.x, tb.y, tb.x + tb.dx, tb.y + tb.dy);
        func_0015FFD0(&font, &tb, 0, &gifs);
        func_0015F0C0(D_002DE760);
        gifs.AddPrimPack(0, 1, 0xE);
        gifs.PackAD(0x61, 0);
        gifs.AddPrimEnd();
        gifs.EndDmaCnt();
        gifs.Detach(0, 0);
    }
}
