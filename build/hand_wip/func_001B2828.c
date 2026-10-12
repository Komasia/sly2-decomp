struct CLOCK { float t; float dt; char pad[0x34]; float t3c; };
extern struct CLOCK D_002DDED0;
struct G { char pad[0x104]; struct H *x104; char pad1[4]; float f10C; int x110; char pad2[0x23C - 0x114]; int x23C; int x240; };
struct H { char pad[8]; char x8[1]; };
extern struct G D_002F66B0;
extern int D_002DE598;
void func_00234A60(int n);
void func_0016F8B8(int a, int b);
void func_0016F6B8(void);
int func_0011D910(void *p, float f);
void func_0016F590(void);
static __inline__ void Draw(int x)
{
    func_0016F8B8(D_002DE598, D_002F66B0.x110 + 0x41BC00);
    if (x) func_0016F8B8(D_002DE598, x);
    func_0016F590();
}
void func_001B2828(void)
{
    struct G *g = &D_002F66B0;
    int x;
    for (;;) {
        g->x240 = 0;
        func_00234A60(g->x23C);
        g->x240 = 1;
        x = 0;
        func_0016F8B8(D_002DE598, g->x110 + 0x3F8E80);
        g->x240 = 2;
        func_0016F6B8();
        if (g->x104 && func_0011D910(g->x104->x8, D_002DDED0.t3c - g->f10C)) x = g->x110 + 0x41DC00;
        Draw(x);
        Draw(x);
    }
}
