// NEAR MISS (Claude agent): 6/191 (hard-reg f5 / v1 vars fixed regs). Remaining: case-3 CLQ init stores vs vsub scheduling (target: por, f1 const, sq 0, swc1 g0, vsub, swc1 g1).
typedef int qword __attribute__((mode(TI)));
struct Q { char pad[0x18]; float x18; float x1C; char pad2[0x30 - 0x20]; int x30; };
struct PO { char pad[0x2DC]; int x2DC; };
struct P { char pad[0x10]; struct PO *p10; char pad2[0x30 - 0x14]; int x30; float x34; void *p38; };
struct CLOCK { float t; };
struct CLQ { float g0, g1, g2, gPad; };
struct LM { float gMin, gMax; };
extern struct CLOCK D_002DDED0;
extern const struct LM D_002A4E58;
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
    __asm__("vmul.xy %0, %1, %1\n\tvaddy.x %0, %0, %0y" : "=j"(t) : "j"(d));
    __asm__ __volatile__("vsqrt Q, %0x\n\tvwaitq\n\tvaddq.x %0, $vf0, Q" : "+j"(t));
    __asm__("qmfc2.ni %0, %1" : "=r"(g) : "j"(t));
    return g;
}
static __inline__ float GFromClq(float g, struct CLQ *pclq) { return pclq->g0 + g * (pclq->g1 + g * pclq->g2); }
static __inline__ void GClamp(float *pg, struct LM *plm)
{
    if (*pg < plm->gMin)
        *pg = plm->gMin;
    else {
        register float gMax __asm__("$f5") = plm->gMax;
        if (gMax < *pg)
            *pg = gMax;
    }
}

static __inline__ float GAtanXY(qword d) { register qword r __asm__("v1"); float x; __asm__("qmfc2.ni %0, %1" : "=r"(r) : "j"(d)); x = GetX(r); { float y; __asm__("prot3w %0,%1" : "=r"(y) : "0"(r)); return func_002458F0(y, x); } }
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
        union { qword q; struct CLQ c; } u;
        struct LM lm;
        qword d;
        float s;
        u.q = 0;
        u.c.g0 = -0.25f;
        u.c.g1 = 0.00156249990686774f;
        lm = D_002A4E58;
        d = Sub(a, b);
        s = GFromClq(LenXY(d), &u.c);
        GClamp(&s, &lm);
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
