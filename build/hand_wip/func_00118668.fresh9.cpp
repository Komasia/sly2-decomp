/* fresh9 (Claude agent, lane D34, 2026-10-24): aligned 5 -> 4. The 2nd Dist is a separate inline Dist2 whose qmfc2 asm has allocation-only tied outputs "+j"(dq), "+j"(oq) (no instructions): the dead one/d stores then depend on the qmfc2, so sched2 issues the mtc1 f6 first (it depends on the last-scheduled insn). Dist returns through a float& (no codegen change). On the shared Dist: 12; a "memory" clobber instead: right order but vf1/vf2 swap (12). Left (3): memset a0 = s4 (cse: ahit canonical). */
/* fresh8 (Claude agent, lane D33, 2026-10-24): aligned 12 -> 5, and the policy-violating `sqc2 "=m"` dead-store asms are gone. The Lerp dead stores to 0x420 are C++ temporaries: `struct VUFT { qword q; VUFT(float f) { qmtc2 asm into q } }` and `qu = VUFT(u).q; qt = VUFT(t).q;` (each temporary is addressable through the inlined ctor, so it gets the one reused temp slot and its store stays; the load is cse-d). qt first then qu: 22. Left: memset a0 = s4 (cse, old) and the 2nd Dist: target mtc1 f6 before the `one` sqc2. */
/* fresh7 (Claude agent, lane D31, 2026-10-24): aligned 15 -> 12. fresh6 plus a separate Lerp2 for phit->pos1 whose vmul output is earlyclobber "=&j": r1 then avoids qu1/qt1 (vf3/vf4) and takes vf1 like the target. Left: memset a0 = s4 (cse), and the qu1/qt1 dead sqc2 stores issue before the vmuls (target: qu1 after the lq/lw of cur.plane, qt1 after all HIT stores). */
/* fresh6 (Claude agent, lane A29, 2026-10-24): aligned 16 -> 15. fresh5 plus a separate LerpT for phit->pos0 whose vmul asm has allocation-only extra operands (3x "j"(qt), 1x "j"(qu)): qt0 vf1, qu0 vf2, qu1 vf3, qt1 vf4 as in the target. Left: memset a0 = s4 (cse), r1 vf3 (target vf1: qu1 must not die at vmul2, i.e. the 2nd Lerp dead stores sit after the vmul at lreg time). */
/* BSP segment clip (fresh rewrite, lane A4). */
typedef int qword __attribute__((mode(TI)));
class VUF {
public:
    VUF();
    qword q;
};
struct VUFT { qword q; VUFT(float f) { __asm__("qmtc2.ni %1, %0" : "=j"(q) : "r"(f)); } };
union U { qword q; float f[4]; };
struct NODE { NODE *pnodeLeft; NODE *pnodeRight; qword *pplane; };
struct ENTRY { NODE *pnode; NODE *pnodeSolid; float t; qword *pplane; qword plane; };
struct HIT { qword pos0; qword pos1; qword plane0; qword plane1; float t0; float t1; int x48; qword *pplane0; qword *pplane1; int pad[3]; };
extern "C" void *func_002333B4(void *pv, int b, unsigned int cb);

static inline NODE *PnodeCheck(NODE *p, NODE *pnodeMax)
{
    if (!(p < pnodeMax))
        p = 0;
    return p;
}

static inline qword Lerp(qword a, qword b, float t)
{
    qword qt, qu, r;
    float u = 1.0f - t;
    qu = VUFT(u).q;
    qt = VUFT(t).q;
    __asm__("vmulax.xyzw $ACC, %1, %2x\n\tvmaddx.xyzw %0, %3, %4x" : "=j"(r) : "j"(a), "j"(qu), "j"(b), "j"(qt));
    return r;
}
static inline qword Lerp2(qword a, qword b, float t)
{
    qword qt, qu, r;
    float u = 1.0f - t;
    qu = VUFT(u).q;
    qt = VUFT(t).q;
    __asm__("vmulax.xyzw $ACC, %1, %2x\n\tvmaddx.xyzw %0, %3, %4x" : "=&j"(r) : "j"(a), "j"(qu), "j"(b), "j"(qt));
    return r;
}
static inline qword LerpT(qword a, qword b, float t)
{
    qword qt, qu, r;
    float u = 1.0f - t;
    qu = VUFT(u).q;
    qt = VUFT(t).q;
    __asm__("vmulax.xyzw $ACC, %1, %2x\n\tvmaddx.xyzw %0, %3, %4x" : "=j"(r) : "j"(a), "j"(qu), "j"(b), "j"(qt), "j"(qt), "j"(qt), "j"(qt), "j"(qu));
    return r;
}

static inline void Dist(qword plane, qword pos, float &gOut)
{
    VUF d;
    VUF one;
    qword dq, oq;
    float g;
    int n;
    __asm__("vmul.xyz %0, %2, %3\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddaz.x $ACC, %1, %0z\n\tvmsubw.x %0, %1, %2w"
            : "=&j"(dq), "=&j"(oq) : "j"(plane), "j"(pos));
    __asm__("qmfc2.ni %0, %1" : "=r"(g) : "j"(dq));
    gOut = g;
    one.q = oq;
    d.q = dq;
}

static inline void Dist2(qword plane, qword pos, float &gOut)
{
    VUF d;
    VUF one;
    qword dq, oq;
    float g;
    int n;
    __asm__("vmul.xyz %0, %2, %3\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddaz.x $ACC, %1, %0z\n\tvmsubw.x %0, %1, %2w"
            : "=&j"(dq), "=&j"(oq) : "j"(plane), "j"(pos));
    __asm__("qmfc2.ni %0, %1" : "=r"(g), "+j"(dq), "+j"(oq)); /* "+j"(dq), "+j"(oq): allocation-only tied operands, no instructions */
    gOut = g;
    one.q = oq;
    d.q = dq;
}

extern "C" int func_00118668(NODE *pnodeRoot, NODE *pnodeMax, qword pos0, qword pos1, int chitMax, HIT *ahit)
{
    ENTRY cur;
    ENTRY aentry[32];
    ENTRY *pentry = aentry;
    HIT *phitPrev = 0;
    struct C32 { int a[8]; } *pc2 = 0, *pc = 0;

    func_002333B4(&cur, 0, sizeof(ENTRY));
    func_002333B4(pentry, 0, sizeof(ENTRY));
    cur.pnode = PnodeCheck(pnodeRoot, pnodeMax);
    pentry->t = 1.0f;

    for (;;) {
        while (!cur.pnode) {
            if (cur.pnodeSolid) {
                if (phitPrev && cur.t == phitPrev->t1) {
                    phitPrev->pos1 = Lerp(pos0, pos1, pentry->t);
                    phitPrev->plane1 = pentry->plane;
                    phitPrev->t1 = pentry->t;
                    phitPrev->pplane1 = pentry->pplane;
                } else {
                    HIT *phit;
                    float t0, t1;
                    if ((int)(pc - (C32 *)0) >= chitMax)
                        return chitMax;
                    phitPrev = ahit;
                    func_002333B4(phitPrev, 0, sizeof(HIT));
                    pc2++; pc++;
                    phit = ahit++;
                    t0 = cur.t;
                    t1 = pentry->t;
                    phit->pos0 = LerpT(pos0, pos1, t0);
                    phit->pos1 = Lerp2(pos0, pos1, t1);
                    phit->plane0 = cur.plane;
                    phit->plane1 = pentry->plane;
                    phit->t0 = t0;
                    phit->t1 = t1;
                    phit->pplane0 = cur.pplane;
                    phit->pplane1 = pentry->pplane;
                }
            }
            if (!(aentry < pentry))
                return pc2 - (C32 *)0;
            cur = *pentry;
            pentry--;
        }
        {
        NODE *pnode = cur.pnode;
        qword plane = *pnode->pplane;
        float d0, d1;
        Dist(plane, pos0, d0);
        Dist2(plane, pos1, d1);
        if (d0 <= 0.0f && d1 <= 0.0f) {
            cur.pnodeSolid = cur.pnode;
            cur.pnode = PnodeCheck(cur.pnode->pnodeLeft, pnodeMax);
        } else if (0.0f < d0 && 0.0f < d1) {
            cur.pnodeSolid = 0;
            cur.pnode = PnodeCheck(cur.pnode->pnodeRight, pnodeMax);
        } else {
            float tSplit = d0 / (d0 - d1);
            float tCur = cur.t;
            float tTop = pentry->t;
            float gCur = d1 * tCur + (1.0f - tCur) * d0;
            float gTop = d1 * tTop + (1.0f - tTop) * d0;
            if (tCur < tSplit && tSplit < tTop) {
                pentry++;
                pentry->t = tSplit;
                pentry->plane = plane;
                pentry->pplane = cur.pnode->pplane;
                if (gCur <= 0.0f) {
                    pentry->pnodeSolid = 0;
                    pentry->pnode = PnodeCheck(cur.pnode->pnodeRight, pnodeMax);
                } else {
                    pentry->pnodeSolid = cur.pnode;
                    pentry->pnode = PnodeCheck(cur.pnode->pnodeLeft, pnodeMax);
                }
            }
            if (gCur < 0.0f || (gCur == 0.0f && gTop <= 0.0f)) {
                cur.pnodeSolid = cur.pnode;
                cur.pnode = PnodeCheck(cur.pnode->pnodeLeft, pnodeMax);
            } else {
                cur.pnodeSolid = 0;
                cur.pnode = PnodeCheck(cur.pnode->pnodeRight, pnodeMax);
            }
        }
        }
    }
}
