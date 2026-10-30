// lilly4 (T1683) C++: EMITV C block as an aggregate initializer with the G4V/CLQ unions (func_0015CAD8 trick)
// lilly1 (Claude agent, T1679): aligned 7 / raw 12 with NO register pin (v4 needed one pin for 7/13). Only change from v3:
// the C block statement order g0,g4,gC,v10,v20,g38,g40,g44,g3C,g68,g60 (statement-order hill-climb, 3 steps, local minimum).
// Left: 0.39 in f0 (target f1), 1.047 in f1 (target f0), -1 in f3 (target reuses 0.39's f1); see notes/150000.md T1679.
// WIP v3 (Claude agent, lane E20): aligned 8 (v2 9). a.x10 store before a.xC via a block temp `int id = px17C->id; a.x10 = x18; a.xC = id;` (sched1 tie on luid). Left: C-block constant f-reg numbers (local-alloc: target 5.0->f2, .39->f1, 1.047->f0, -1->f1).
typedef int qword __attribute__((mode(TI)));
typedef struct VTE { short d; short pad; qword (*pfn)(void *); } VTE;
typedef struct VT { VTE a[64]; } VT;
typedef struct XE8 { char pad[0x80]; qword v; } XE8;
typedef struct SO { int x0, x4, x8; VT *pvt; char pad10[0xE8 - 0x10]; XE8 *pxE8; } SO;
typedef struct SND { char pad[0x170]; float t; void *psnd; } SND;
typedef struct EVT { short d; short pad; void (*pfn)(void *, float, qword, int); } EVT;
typedef struct EVTT { EVT a[4]; } EVTT;
typedef struct EX { char pad[0x18]; int id; } EX;
typedef struct WATER { char pad[0x18]; int x18; char pad1c[0x178 - 0x1C]; EX *px178; EX *px17C; int x180; } WATER;
typedef struct RIP { char pad[0x1C]; EX *pex; float g20; float g24; char pad28[0xEC - 0x28]; EVTT *pvt; } RIP;
struct A { int x0; int x4; int x8; int xC; int x10; int x14; float g18; float g1C; float g20; int pad[7]; } __attribute__((aligned(16)));
union CLQ { struct { float g0, g1, g2, gUnused; }; float ag[4]; };
union G4V { struct { float g0, g4, g8, gC; }; float ag[4]; };
typedef struct C { G4V g0; qword v10; qword v20; int x30, x34; float g38; float g3C; float g40; float g44;
    int pad48[6]; CLQ clq60; } C;
typedef struct E { int x0, x4; EX *p8; EX *pC; WATER *p10; int x14, x18, x1C; qword v; int pad[4]; } E;
typedef struct CLOCK { float t; } CLOCK;

extern "C" {
extern CLOCK D_002DDED0;
extern int D_002BDEB0[];
extern qword D_002A2DC0;
extern char D_003DD490[];
extern float func_0011D448(float lo, float hi);
extern int func_0011D3F8(int lo, int hi);
extern int func_00132B10(SO *p, int n);
extern void func_001FB1F8(void *p, float g);
extern void func_001FB098(void *p, float g);
extern void *func_001FBB90(int id);
extern void func_001FB2F8(void *p, SO *pso);
extern void func_001FB4F0(void *p, float a, float b);
extern void func_00258040(void *pp, void *p);
extern RIP *func_001CE888(void *p, int k, int x);
extern void *func_002333B4(void *p, int c, int cb);
extern void func_0015BE28(qword pos, qword dir, int n, A *pa, C *pc, E *pe, int x, int y);

}
static inline qword Length(qword a)
{
    qword r, one;
    __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z\n\t"
            "vsqrt $Q, %0x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q"
        : "=j"(r), "=j"(one) : "j"(a));
    return r;
}
static inline qword Sub(qword a, qword b)
{
    qword r;
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b));
    return r;
}
static inline float GClamp(float g, float lo, float hi)
{
    if (g < lo)
        return lo;
    if (hi < g)
        return hi;
    return g;
}
static inline float GetX(qword q)
{
    float f;
    __asm__("mtc1 %1, %0" : "=f"(f) : "r"(q));
    return f;
}

void WakeSoWater(SO *p, WATER *pwater, qword pos, qword v, float dt, float gFrac, float gScale) __asm__("WakeSoWater__FP2SOP5WATERfP6VECTORT3ff");
void WakeSoWater(SO *p, WATER *pwater, qword pos, qword v, float dt, float gFrac, float gScale)
{
    float g = 0.0f;
    VTE *pvte = &p->pvt->a[33];
    float d = GetX(Length(Sub(pos, pvte->pfn((char *)p + pvte->d))));
    int fWake = func_0011D448(g, 3.0f) < dt;
    SND *psnd;
    float t, u;
    psnd = 0;
    if (func_00132B10(p, 0x32))
        psnd = (SND *)p;
    if (d > 10.0f || fWake) {
        u = (d - 10.0f) * 0.0012658228f; t = GClamp(u, g, 1.0f);
        if (psnd && pwater->x180) {
            void **pp = &psnd->psnd;
            g = t * 0.9f + 0.1f;
            if (psnd->psnd) {
                func_001FB1F8(psnd->psnd, g);
            } else {
                void *ps = func_001FBB90(D_002BDEB0[func_0011D3F8(0, 3)]);
                func_001FB2F8(ps, (SO *)psnd);
                func_001FB4F0(ps, 100.0f, 1000.0f);
                func_001FB1F8(ps, g);
                func_00258040(pp, ps);
            }
        }
        if (!fWake) {
            u = 1.0f - t * (1.0f - gFrac);
            if (psnd) {
                fWake = u < D_002DDED0.t - psnd->t;
            } else {
                float tc = D_002DDED0.t;
                int c0 = (int)(tc / u);
                int c1 = (int)((tc + dt) / u);
                fWake = c0 != c1;
            }
        }
        if (fWake && pwater->px17C) {
            RIP *prip = func_001CE888(D_003DD490, 7, 0);
            if (prip) {
                EVT *pe = &prip->pvt->a[1];
                pe->pfn((char *)prip + pe->d, gScale, v, 0);
                prip->g20 = gScale;
                prip->g24 = gScale * 0.6f;
                prip->pex = pwater->px17C;
                if (psnd)
                    psnd->t = D_002DDED0.t;
                if (500.0f < d && pwater->px178) {
                    A b = { 1, 0, pwater->px178->id, pwater->px17C->id, pwater->x18, 0, 8.0f, 12.0f, 1.0f };
                    C dd = { {{ d * 0.5f, d * 0.75f, 0.0f, 1.0f }}, p->pxE8->v, D_002A2DC0, 0, 0,
                             1.0f, 5.0f, 0.39269909f, 1.0471976f, { 0 }, {{ 1.0f, 0.0f, -1.0f }} };
                    {
                        E e;
                        func_002333B4(&e, 0, 0x14);
                        e.v = v;
                        ((float *)&e.v)[2] += 30.0f;
                        e.p8 = pwater->px178;
                        e.pC = pwater->px17C;
                        e.p10 = pwater;
                        func_0015BE28(e.v, D_002A2DC0, func_0011D3F8(4, 6), &b, &dd, &e, 0, 0);
                    }
                }
            }
        }
    } else if (psnd) {
        void **pp = &psnd->psnd;
        if (pp && *pp) {
            func_001FB098(*pp, g);
            func_00258040(pp, 0);
        }
    }
}
