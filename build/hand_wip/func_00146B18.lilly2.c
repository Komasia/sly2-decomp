// lilly2 (Claude agent for Lilly, T1653 2026-10-25): aligned 3. v4 with the vmul/vaddy asm reading "m"(clq.g0) (allocation-only input,
// no "memory" clobber). sched1 is now RIGHT: the g0 store gets prio 22 > g1 store 21, so the clear (200) ties the f1 const (206) at 23 and
// wins on dependents -> por is emitted before the f1 const. Left: in sched2 the a reload (lqc2 vf1,0x40) ties 206 at prio 24 and wins on
// dependents (5 vs 3), so lqc2/vsub move above the f1 const. Needed: 206 at 25 in sched2 while the g0 chain stays longer in sched1.
// v4 (Claude agent, laneC44 2026-10-24): aligned 2 -> 1. LenXY split into SqXY (vmul/vaddy with a commented "memory" clobber) and SqrtQ, with the lm initializer between them (the target copies lm between vaddy and vsqrt): swc1 g0 now issues before the vsub. Left: por (clq clear reload) after the f1 constant.
// v3 (Claude agent, laneC2b): same aligned 2 as v2, but the union u is replaced by a local initializer `struct CLQ clq = {-0.25f, 0.0015625f}` (CLQ aligned(16)), same code. Left: sched2 luid ties (f1 const 206 vs por reload 536; vsub 221 vs swc1 g0 204).
// v2 (Claude agent, laneC2a 2026-10-23): aligned 2, now ONE pin (v1). The f5 pin is gone: the clamp is a GLimitLm(plm, g) inline
// that reads gMin and gMax into locals up front, and lm is a local `struct LM lm = {0.1f, 1.0f}` (D_002A4E58 is its .rodata
// initializer, not a named global). Left: por (u.q = 0 reload) after the f1 constant, and swc1 g0 after vsub (sched2 ties).
// NEAR MISS (Claude agent): 6/191 (hard-reg f5 / v1 vars fixed regs). Remaining: case-3 CLQ init stores vs vsub scheduling (target: por, f1 const, sq 0, swc1 g0, vsub, swc1 g1).
typedef int qword __attribute__((mode(TI)));
struct Q { char pad[0x18]; float x18; float x1C; char pad2[0x30 - 0x20]; int x30; };
struct PO { char pad[0x2DC]; int x2DC; };
struct P { char pad[0x10]; struct PO *p10; char pad2[0x30 - 0x14]; int x30; float x34; void *p38; };
struct CLOCK { float t; };
struct CLQ { float g0, g1, g2, gPad; } __attribute__((aligned(16)));
struct LM { float gMin, gMax; };
extern struct CLOCK D_002DDED0;
void func_001EF0C0(struct P *p, struct Q *q);
qword func_001A62E8(void *p);
float func_002458F0(float y, float x);
void func_001C45A8(struct Q *q);
static __inline__ float GetX(qword q) { float x; __asm__("mtc1 %1,%0" : "=f"(x) : "r"(q)); return x; }
static __inline__ float GetY(qword q) { float y; __asm__("prot3w %0,%1" : "=r"(y) : "r"(q)); return y; }
static __inline__ qword Sub(qword a, qword b) { qword d; __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(a), "j"(b)); return d; }
static __inline__ float LenXY(qword d)
{
    float g;
    qword t;
    __asm__("vmul.xy %0, %1, %1\n\tvaddy.x %0, %0, %0y" : "=j"(t) : "j"(d) : "memory");
    __asm__ __volatile__("vsqrt Q, %0x\n\tvwaitq\n\tvaddq.x %0, $vf0, Q" : "+j"(t));
    __asm__("qmfc2.ni %0, %1" : "=r"(g) : "j"(t));
    return g;
}
/* "memory" clobber (Claude agent): the clq stores (swc1 g0 before the vsub) must finish before the vmul, like the target */
static __inline__ qword SqXY(qword d) { qword t; __asm__("vmul.xy %0, %1, %1\n\tvaddy.x %0, %0, %0y" : "=j"(t) : "j"(d)); return t; }
static __inline__ float SqrtQ(qword t)
{
    float g;
    __asm__ __volatile__("vsqrt Q, %0x\n\tvwaitq\n\tvaddq.x %0, $vf0, Q" : "+j"(t));
    __asm__("qmfc2.ni %0, %1" : "=r"(g) : "j"(t));
    return g;
}
static __inline__ float GFromClq(float g, struct CLQ *pclq) { return pclq->g0 + g * (pclq->g1 + g * pclq->g2); }
static __inline__ float GLimitLm(struct LM *plm, float g)
{
    float gMin = plm->gMin, gMax = plm->gMax;
    if (g < gMin)
        return gMin;
    if (gMax < g)
        return gMax;
    return g;
}
static __inline__ float GAtanXY(qword d) { register qword r __asm__("v1"); /* register pin (Claude agent) */ float x; __asm__("qmfc2.ni %0, %1" : "=r"(r) : "j"(d)); x = GetX(r); { float y; __asm__("prot3w %0,%1" : "=r"(y) : "0"(r)); return func_002458F0(y, x); } }
void func_00146B18(struct P *p, struct Q *q)
{
    func_001EF0C0(p, q);
    switch (p->x30) {
    case 1: {
        qword d = Sub(func_001A62E8(p->p38), func_001A62E8(p->p10));
        q->x1C = 1.0f;
        q->x18 = func_002458F0(GetY(d), GetX(d));
        break;
    }
    case 2: {
        qword d = Sub(func_001A62E8(p->p38), func_001A62E8(p->p10));
        q->x1C = 1.0f;
        q->x18 = func_002458F0(GetY(d), GetX(d));
        if (D_002DDED0.t - p->x34 < 0.1f) {
            q->x30 |= 0x80;
            func_001C45A8(q);
        }
        break;
    }
    case 3: {
        qword a = func_001A62E8(p->p38);
        qword b = func_001A62E8(p->p10);
        struct CLQ clq = {-0.25f, 0.00156249990686774f};
        qword d;
        float s;
        {
        qword t;
        d = Sub(a, b);
        __asm__("vmul.xy %0, %1, %1\n\tvaddy.x %0, %0, %0y" : "=j"(t) : "j"(d), "m"(clq.g0));
        {
        struct LM lm = {0.1f, 1.0f};
        s = GLimitLm(&lm, GFromClq(SqrtQ(t), &clq));
        }
        }
        q->x1C = s;
        q->x18 = GAtanXY(d);
        if (D_002DDED0.t - p->x34 < 0.1f && p->p10->x2DC == -1) {
            q->x30 |= 0x40;
            func_001C45A8(q);
        }
        break;
    }
    case 4: {
        qword d = Sub(func_001A62E8(p->p38), func_001A62E8(p->p10));
        q->x1C = 1.0f;
        q->x18 = func_002458F0(GetY(d), GetX(d));
        if (D_002DDED0.t - p->x34 < 0.1f) {
            q->x30 |= 0x80;
            func_001C45A8(q);
        }
        break;
    }
    }
}
