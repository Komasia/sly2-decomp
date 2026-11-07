struct E { int n0; int n4; int n8; float gC; int pad10; int n14; int n18; int n1C; int n20; };
struct S {
    char pad0[0x50]; int n50; char pad54[0x5C - 0x54]; float g5C;
    char pad60[0x1C0 - 0x60]; int c1C0; struct E a1C4[3];
    int n230; char pad234[0x284 - 0x234]; float g284; float g288; char x28C[0x18]; float g2A4;
};
struct CLOCK { float t; float dt; };
extern struct CLOCK g_clock;
extern char D_003DD040[];
extern char g_game[];
void func_001A5E28(struct S *);
float TMusicTop__FPv(void *);
void PlayDancerMove__FP2LOiii(int, int, int, int);
void BroadcastTaskEvent__FP2SWiP2LO(void *, int, struct S *);
void AddDanceScore__FP2LOiif(struct S *, float);
float GSmooth__FfffP3SMPPf(void *, float, float, float, int);
void UpdateDanceCrowd__FP5DANCE(struct S *);
// name: SafeHouse port (UpdateDance)
void UpdateDance__FP2LO(struct S *p)
{
    float t;
    int i, j;
    struct E *pe;
    func_001A5E28(p);
    t = TMusicTop__FPv(D_003DD040);
    switch (p->n50) {
    case 1:
        for (j = 0; j < p->c1C0; j++) {
            pe = &p->a1C4[j];
            if (pe->n14)
                continue;
            if (pe->gC < t) {
                PlayDancerMove__FP2LOiii(pe->n0, pe->n4, pe->n8, 0);
                pe->n14 = 1;
                break;
            }
        }
        break;
    case 2:
        for (i = 0; i < p->c1C0; i++) {
            pe = &p->a1C4[i];
            if (pe->n20)
                continue;
            if (!pe->n18 && pe->gC < t) {
                p->n230 = pe->n4;
                BroadcastTaskEvent__FP2SWiP2LO(g_game, 0x34, p);
                pe->n18 = 1;
            }
            if (pe->gC + p->g5C < t) {
                pe->n20 = 1;
                if (!pe->n1C) {
                    PlayDancerMove__FP2LOiii(pe->n0, pe->n4, pe->n8, 2);
                    AddDanceScore__FP2LOiif(p, p->g2A4);
                }
                break;
            }
        }
        break;
    }
    { float dt = g_clock.dt; p->g288 = GSmooth__FfffP3SMPPf(p->x28C, p->g288, p->g284, dt, 0); }
    UpdateDanceCrowd__FP5DANCE(p);
}
