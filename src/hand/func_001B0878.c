struct R { int tagk; int tag; };
struct G1 { char pad[0x4C]; int x4C; };
struct G2 { char pad[0xFD50]; int xFD50; };
struct S { char pad[0x1C]; int f; };
extern char g_game[], D_003D4A60[];
extern struct G1 D_002E6550;
extern struct G2 D_002E65E0;
extern int D_003E0FE4;
void BroadcastTaskEvent__FP2SWiP2LO(void *p, int a, int b);
void NProgress(struct R *r, int a, void *b);
void Decref(struct R *r) asm("Decref__4CRef");
void func_001ACB58(struct G1 *p, int n);
void func_001ABD40(struct G2 *p);
void func_001660F8(void);
void func_001B0878(struct S *p)
{
    BroadcastTaskEvent__FP2SWiP2LO(g_game, 0x2D, 0);
    BroadcastTaskEvent__FP2SWiP2LO(g_game, 0x2E, 0);
    if (D_002E65E0.xFD50) {
        struct R r;
        int v;
        D_002E6550.x4C = 1;
        NProgress(&r, D_003E0FE4, D_003D4A60);
        v = r.tag;
        Decref(&r);
        if (v == 0) {
            func_001ACB58(&D_002E6550, 0x22);
        } else {
            func_001ACB58(&D_002E6550, 0x1A);
            func_001ABD40(&D_002E65E0);
        }
    } else {
        func_001660F8();
    }
    if (p) p->f |= 2;
}
