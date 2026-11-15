// Aim (Claude agent, lane D16). From v4: the vsub reads q (the pinned Add result) with `posT = q` after it, and its posMe operand is repeated as an allocation-only operand (reload then puts posMe in vf4 like the target).
#include "cid.h"
#include "so.h"
struct VU_FLOAT { qword q; VU_FLOAT(float f) { __asm__("qmtc2.ni %1, %0" : "=j"(q) : "r"(f)); } };
struct G;
// a breakable (cid 0x62): an SO on the breakables list D_003E1450 (slots 22 / 23 of the class add / remove it)
struct BREAKABLE { SO so; char unk_0x150[0x174 - 0x150]; DLE dleBreakable; };
// a point (cid 0x12, an XFM), as found around a breakable
struct PNT { XFM xfm; char unk_0xe0[0xE8 - 0xE0]; int grf; float sRadius; };
struct PATH { char pad[0x90]; int c; qword *av; };
struct PSO { char pad[0xC]; VTENT *vt; char pad1[0x258 - 0x10]; PATH *ppath; char pad2[0x2DC - 0x25C]; int x2DC; };
struct W { char pad[0x1010]; LO *plo; };
struct P { char pad[0x10]; W *pw; char pad1[0x48 - 0x14]; float t48; };
#include "clock.h"
extern "C" {
extern G g_sw;
extern BREAKABLE *D_003E1450;   // the breakables list (a DL: its head)
extern float D_002BD460;
extern float D_002BD468[2];
extern float D_002BD470, D_002BD474, D_002BD478, D_002BD47C;
PSO *PloPlayerPo(G *pg) asm("PloPlayerPo__FP2SW");
qword PosOfLo(void *p) asm("PosOfLo__FP2LO");
float GRandInRange(float a, float b) asm("GRandInRange__Fff");
int IsSwHandsOff(G *pg) asm("IsSwHandsOff__FP2SW");
int FIsBasicDerivedFrom(PSO *p, int n) asm("FIsBasicDerivedFrom__FP5BASIC3CID");
void SetGuardPursued(W *pw, void *p) asm("SetGuardPursued__FP5GUARDP2LO");
int func_001BBE48(BREAKABLE *pbrk);   // the breakable is broken
int CFindObjectsByClass(G *pg, int grffso, int cid, void *ploContext, int cploMax, PNT **apnt) asm("CFindObjectsByClass__FP5BASICiiPP5BASICiPP2LO");
int NRandInRange(int a, int b) asm("NRandInRange__Fii");
qword SetVectorSphere(float a, float b, float c) asm("SetVectorSphere__Ffff");
float RadBetweenVectors(qword a, qword b, void *p) asm("RadBetweenVectors__FG9VU_VECTORT0P6VECTOR");
float atan2f(float y, float x) asm("atan2f");
qword SetVectorCylind(float a, float b, float c) asm("SetVectorCylind__Ffff");
void Aim(P *p) asm("Aim__8JOBCHASE");
}
static inline int FLess(float a, float b) { return a < b; }
static inline qword Sub(qword a, qword b) { qword r; __asm__("vsub.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword SubX(qword a, qword b) { qword r; __asm__("vsub.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b), "j"(b)); /* extra operand: allocation only */ return r; }
static inline qword Add(qword a, qword b) { qword r; __asm__("vadd.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline float Len(qword a)
{
    qword d, one; float g;
    __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=&j"(d), "=&j"(one) : "j"(a));
    __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(d) : "j"(d));
    __asm__("qmfc2.ni %0, %1" : "=r"(g) : "j"(d));
    return g;
}
static inline float LenSq(qword a)
{
    qword d, one; float g;
    __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(d), "=&j"(one) : "0"(a));
    __asm__("mtc1 %1, %0" : "=f"(g) : "r"(d));
    return g;
}
static inline float Len2(qword a)
{
    qword d; float g;
    __asm__("vmul.xy %0, %1, %1\n\tvaddy.x %0, %0, %0y" : "=&j"(d) : "j"(a));
    __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(d) : "j"(d));
    __asm__("qmfc2.ni %0, %1" : "=r"(g) : "j"(d));
    return g;
}
static inline float GetX(qword q) { float x; __asm__("mtc1 %1, %0" : "=f"(x) : "r"(q)); return x; }
static inline float GetY(qword q) { float y; __asm__("prot3w %0, %1" : "=r"(y) : "r"(q)); return y; }
static inline float GetZ(qword q) { float z; __asm__("pextuw %0, $0, %1" : "=r"(z) : "r"(q)); return z; }
static inline qword AddScaledNorm(qword a, qword v, VU_FLOAT s)
{
    qword d, one, r;
    __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=&j"(d), "=&j"(one) : "j"(v));
    __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(d) : "j"(d));
    __asm__("vdiv $Q, $vf0w, %1x\n\tvwaitq\n\tvmulq.xyzw %0, %2, $Q" : "=j"(d) : "j"(d), "j"(v));
    __asm__("vadda.xyzw $ACC, %1, $vf0\n\tvmaddx.xyzw %0, %2, %3x" : "=j"(r) : "j"(a), "j"(d), "j"(s.q));
    return r;
}

// name: SafeHouse port (JOBCHASE::Aim)
void Aim(P *p)
{
    G *pg = &g_sw;
    PSO *pso = PloPlayerPo(pg);
    qword posPlayer = PosOfLo(pso);
    qword posMe = PosOfLo(p->pw);
    qword d = Sub(posPlayer, posMe);
    qword v;
    qword pos;
    {
        VTENT *e = &pso->vt[33];
        v = ((qword (*)(void *))e->pfn)(VT_THIS(pso, e));
    }
    if (FLess(D_002BD460, Len(v)))
        p->t48 = g_clock.t;
    float dt = g_clock.t - p->t48;
    if (GRandInRange(D_002BD468[0], D_002BD468[1]) < dt && !IsSwHandsOff(pg)) {
        if (FIsBasicDerivedFrom(pso, CID_ACTOR) && pso->x2DC == 0x11) {
            PATH *ppath = pso->ppath;
            pos = PosOfLo(pso);
            int c = ppath->c;
            for (int i = 0; i < c; i++) {
                if (GetZ(pos) < GetZ(ppath->av[i]))
                    pos = ppath->av[i];
            }
            goto done;
        }
        SetGuardPursued(p->pw, pso);
        return;
    }
    for (BREAKABLE *pbrk = D_003E1450; pbrk; pbrk = (BREAKABLE *)pbrk->dleBreakable.next) {
        if (!func_001BBE48(pbrk)) {
            PNT *apnt[8];
            qword posT = PosOfLo(pbrk);
            float r = D_002BD478;
            if (pbrk->so.ptree) {   // its bounds
                posT = pbrk->so.ptree->qwCenter;
                r = pbrk->so.ptree->sRadius;
            }
            int c = CFindObjectsByClass(&g_sw, 1, 0x12, pbrk, 8, apnt);   // its points (cid 0x12)
            int k = 0;
            for (int i = 0; i < c; i++) {
                if (apnt[i]->grf & 0x17E)
                    apnt[k++] = apnt[i];
            }
            if (k) {
                PNT *pnt = apnt[NRandInRange(0, k - 1)];
                posT = PosOfLo(pnt);
                r = pnt->sRadius;
            }
            if (!FLess(D_002BD478 * D_002BD478, LenSq(Sub(posT, posPlayer)))) {
                float pan = GRandInRange(-3.1415927f, 3.1415927f);
                float tilt = GRandInRange(-3.1415927f, 3.1415927f);
                register qword q asm("vf3"); /* register pin: the target's vadd writes posT's new value to vf3 */
                q = Add(posT, SetVectorSphere(pan, tilt, GRandInRange(0.0f, r)));
                qword e = SubX(q, posMe);
                posT = q;
                if (FLess(Len2(e), Len2(d))) {
                    pos = posT;
                    goto done;
                }
                float g = RadBetweenVectors(d, e, 0);
                if (!(__builtin_fabsf(g) * 57.295776f <= D_002BD47C)) {
                    pos = posT;
                    goto done;
                }
            }
        }
    }
    if (FLess(Len2(v), D_002BD460)) {
        qword e = Sub(posMe, posPlayer);
        float rad = atan2f(GetY(e), GetX(e));
        qword pp = PosOfLo(pso);
        pos = Add(pp, SetVectorCylind(GRandInRange(rad - 1.5707964f, rad + 1.5707964f), D_002BD470, D_002BD474));
    } else {
        pos = AddScaledNorm(posPlayer, v, VU_FLOAT(-D_002BD470));
    }
done:
    {
        LO *plo = p->pw->plo;
        VTENT *e = &plo->pvt[29];
        ((void (*)(void *, qword))e->pfn)(VT_THIS(plo, e), pos);
    }
    SetGuardPursued(p->pw, p->pw->plo);
}
