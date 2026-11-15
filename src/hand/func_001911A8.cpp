// UpdateInteractTransitions__FP5ACTOR: per-frame update of a hero's interaction (ACTOR::inter, +0x4C0; UpdateBentleyTransitions calls it in
// its state 3). It dispatches on the context's action and loops while the action changed the step (and not to -1).
// Action 8 / step "other" probes the ground below the actor: a box query along the actor's up axis, a line test
// against every found object (any hit with a nonzero parameter aborts), then a sphere around the actor's world bounds
// is pruned against every object's BSP and turned into contacts; any contact aborts, otherwise step 8 is entered.
//
// Matching notes (wave-4 lane 8):
// - case 8 switches on p->state (the field, not the loop's local): gcse turns the load into a copy of the loop-top
//   load, which gives the `lw a1, state` in the dispatch branch's delay slot; the local itself is spilled.
// - ProbeGround's exits are plain returns out of a STACKSCOPE scope (out-of-line ctor/dtor 0x1AE478/0x1AE4A0);
//   loop.c moves the `{ FreeSwXpList(); return; }` block out of the contact loop into the default case.
// - case 2 has its own SetControl for the `<= 0` test: the shared SetControl then has no label in front of it, so
//   jump2's cross-jumping makes a new label there and does not merge the step-8 / case-11 anim tests afterwards.
// - GLength takes a const reference (gcse hash table size, i.e. the order of the &cso / &apso copies: s4 / s6).
#include "cid.h"
#include "actor.h"
#include "po.h"

struct SURF;
struct BSP { BSP *pbspNeg, *pbspPos; SURF *psurf; };
struct XP;
struct ASEGA;
// Line segment hit (0x60 bytes, as in SphereBspContacts)
struct LSG { qword apos[2]; qword anormal[2]; float au[2]; int lsgk; void *apsurf[2]; void *pedge; int iiposSwap; LSG *plsgNext; };
#include "clock.h"
struct SWALLOC { int cb, cbAlign; };
struct STACKSCOPE { STACKSCOPE(); ~STACKSCOPE(); };   // 0x1AE478 / 0x1AE4A0(this, 2)
struct VU_FLOAT { qword q; };

extern "C" {
extern uint g_grfusr;
extern qword g_normalZ;                                // (0, 0, 1)
extern float D_002BF5B0, D_002BF5B4, D_002BF5B8;
int GrfPadctlTakePressed(POCTL *, uint, float) asm("GrfPadctlTakePressed__FP6PADCTL");
int GrfPadctlPressedWithin(POCTL *, uint, float) asm("GrfPadctlPressedWithin__FP6PADCTLUif");
void ForgetPadctlPresses(POCTL *, uint) asm("ForgetPadctlPresses__FP6PADCTLUi");
void SetJumpKind(JUMP *, int, int, LO *) asm("SetJumpKind__FP4JUMPiiP2LO");
void OpenBinoc(void *, int, int, int) asm("OpenBinoc__FP5ACTORiP2LOT2");
int FAsegaRetracted(ASEGA *) asm("FAsegaRetracted__FP5ASEGA");
void SetInteractState(INTERACT *, int) asm("SetInteractState__FP5ACTORi");                     // set the step
void *PvAllocStackImpl(SWALLOC *) asm("PvAllocStackImpl__Fi");                         // stack allocation in the current STACKSCOPE
qword PosOfLo(void *) asm("PosOfLo__FP2LO");                           // world position
int NOverlapKind(void *, SOPART *) asm("NOverlapKind__FP3ALOT0");
void func_0020FAA0(SW *, qword, qword, int (*)(void *, SOPART *), SOTREE *, int *, SOPART ***);   // objects in a box
int ClipSegmentSoe(SOPART *, qword, qword, int, LSG *) asm("ClipSegmentSoe__FP3SOEG9VU_VECTORT1iP3LSG");      // line test against an object
void UpdateSoeWorld(SOPART *) asm("UpdateSoeWorld__FP3SOE");
qword func_0011F288(int, VECTOR *);                      // min of points
qword func_0011F2B8(int, VECTOR *);                      // max of points
void MarkSphereBsp(SW *, SOPART *, SOPART *, int, BSP *, XP **) asm("MarkSphereBsp__FP3SOET0PviPP2XPPP7CONTACT");
int ClipBspPlane(BSP *, BSP *, float, qword, int *, BSP **) asm("ClipBspPlane__FP6BSPREFP6VECTORG9VU_VECTORfPiPP4NODE");   // prune a BSP to a sphere
void MarkBspBsp(SW *, SOPART *, SOPART *, int, BSP *, BSP *, XP **) asm("MarkBspBsp__FP3SOET0P5SHAPEiP6BSPSELPP2XPPP7CONTACT");
void AttachReachObject(REACH *, LO *) asm("AttachReachObject__FP5REACHP2LO");
int FIsBasicDerivedFrom(LO *, int) asm("FIsBasicDerivedFrom__FP5BASIC3CID");
int FActorPoseDone(ACTOR *) asm("FActorPoseDone__FP5ACTOR");
int NActorPower__FP5ACTOR(ACTOR *);
uint GrfAbilityButton__FP5ACTORi(ACTOR *, int);
}
void FreeSwXpList(SW *, XP *);

static inline void SetControl(ACTOR *p, int n) { VTENT &v = p->so.lo.pvt[88]; ((void (*)(void *, int))v.pfn)(VT_THIS(p, &v), n); }
static inline int CanAct(ACTOR *p, int n) { VTENT &v = p->so.lo.pvt[99]; return ((int (*)(void *, int))v.pfn)(VT_THIS(p, &v), n); }
static inline void Notify(LO *p, ACTOR *q) { VTENT &v = p->pvt[51]; ((void (*)(void *, ACTOR *))v.pfn)(VT_THIS(p, &v), q); }
// the interaction's target object
static inline LO *PloTarget(INTERACT *p) { return (LO *)p->ploTarget; }
static inline void *PvAllocStack(int cb) { SWALLOC swalloc; swalloc.cb = cb; swalloc.cbAlign = 0x10; return PvAllocStackImpl(&swalloc); }

static inline VU_FLOAT VuFloat(float g) { VU_FLOAT v; __asm__("qmtc2.ni %1,%0" : "=j"(v.q) : "r"(g)); return v; }
// The never-chosen "V" alternative is allocation-only: the word stays a MEM until reload (as in PosCmAvoid).
static inline VU_FLOAT VuFloat(const float *pg) { VU_FLOAT v; __asm__("qmtc2.ni %1,%0" : "=j,j"(v.q) : "r,V"(*(const int *)pg)); return v; }
static inline qword QwAdd(qword a, qword b) { qword r; __asm__("vadd.xyzw %0,%1,%2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword QwSub(qword a, qword b) { qword r; __asm__("vsub.xyzw %0,%1,%2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword QwScale(qword a, VU_FLOAT g) { qword r; __asm__("vmulx.xyzw %0,%1,%2x" : "=j"(r) : "j"(a), "j"(g.q)); return r; }
// a * g0 + b * g1
static inline qword QwCombine(qword a, qword b, VU_FLOAT g0, VU_FLOAT g1)
{
    qword r;
    __asm__("vmulax.xyzw $ACC,%1,%2x\n\tvmaddx.xyzw %0,%3,%4x" : "=j"(r) : "j"(a), "j"(g0.q), "j"(b), "j"(g1.q));
    return r;
}
static inline float GFromVf(qword v) { float g; __asm__("qmfc2.ni %0,%1" : "=r"(g) : "j"(v)); return g; }
static inline float GLength(const qword &v)
{
    qword qw, one;
    __asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z" : "=j"(qw), "=j"(one) : "j"(v));
    __asm__("vsqrt $Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q" : "=j"(qw) : "0"(qw));
    return GFromVf(qw);
}
static inline int Min(int a, int b) { return a < b ? a : b; }
static inline int FWithin(qword a, qword b, float s) { return GLength(QwSub(a, b)) < s; }

static inline void ProbeGround(INTERACT *p)
{
    STACKSCOPE scope;
    LSG alsg[8];
    int i;
    qword pos = PosOfLo(p->pactor);
    qword posBase = QwAdd(pos, p->pactor->vecBase);
    qword posEnd = QwAdd(posBase, QwScale(g_normalZ, VuFloat(&D_002BF5B0)));
    int cso;
    SOPART **apso;
    func_0020FAA0(&g_sw, posEnd, posBase, NOverlapKind, p->pactor->so.ptree, &cso, &apso);
    for (i = 0; i < cso; i++) {
        int clsg = ClipSegmentSoe(apso[i], posBase, posEnd, 8, alsg);
        LSG *plsg = alsg;
        for (int j = 0; j < clsg; j++)
            if (plsg[j].au[0] != 0.0f)
                return;
    }
    SOPART *psoSelf = p->pactor->psoeSource;
    GEOM *pgeom = &psoSelf->geomWorld;
    int cbspMax = 0;
    UpdateSoeWorld(psoSelf);
    qword posMin = func_0011F288(pgeom->cpos, pgeom->apos);
    qword posMax = func_0011F2B8(pgeom->cpos, pgeom->apos);
    func_0020FAA0(&g_sw, posMin, posMax, NOverlapKind, p->pactor->so.ptree, &cso, &apso);
    for (i = 0; i < cso; i++)
        if (cbspMax <= apso[i]->bspc.cbspFull)
            cbspMax = apso[i]->bspc.cbspFull;
    cbspMax = Min(cbspMax, 0x1555);
    BSP *absp = (BSP *)PvAllocStack(cbspMax * sizeof(BSP));
    qword posMid = QwCombine(posMin, posMax, VuFloat(0.5f), VuFloat(0.5f));
    float sRadius = GLength(QwSub(posMid, posMin));
    for (i = 0; i < cso; i++) {
        SOPART *pso = apso[i];
        XP *pxp = 0;
        if (pso->fUnk49) {
            MarkSphereBsp(&g_sw, pso, psoSelf, 0, 0, &pxp);
        } else {
            int cbspLeft = cbspMax;
            BSP *pbsp = absp;
            if (ClipBspPlane(pso->bspc.absp, (BSP *)0x7FFFFFFF, sRadius, posMid, &cbspLeft, &pbsp) == 2) {
                int cbsp = pbsp - absp;
                pbsp--;
                MarkBspBsp(&g_sw, psoSelf, pso, cbsp, pso->bspc.absp, pbsp, &pxp);
            }
        }
        if (pxp) {
            FreeSwXpList(&g_sw, pxp);
            return;
        }
    }
    SetInteractState(p, 8);
}

// name: SafeHouse port (UpdateInteractTransitions)
extern "C" void UpdateInteractTransitions__FP5ACTOR(INTERACT *p)
{
    POCTL *pctl = p->pactor->pctl;
    int state;
    do {
        state = p->state;
        switch (p->kind) {
        case 1:
            if (0.15f < g_clock.t - p->tState && GrfPadctlTakePressed(pctl, 0x40, 0.25f)) {
                SetJumpKind(&p->pactor->jump, 7, 0, PloTarget(p));
                break;
            }
            if (GrfPadctlPressedWithin(pctl, 0x400, 0.15f) && CanAct(p->pactor, 3)) {
                ForgetPadctlPresses(pctl, 0x400);
                OpenBinoc((char *)p->pactor + 0xF00, 0, 0, 0);
            }
            break;
        case 3:
        case 4:
            if (GrfPadctlTakePressed(pctl, 0x40, 0.1f)) {
                SetJumpKind(&p->pactor->jump, 1, 0, 0);
                break;
            }
            if (GrfPadctlPressedWithin(pctl, 0x400, 0.15f) && CanAct(p->pactor, 3)) {
                ForgetPadctlPresses(pctl, 0x400);
                OpenBinoc((char *)p->pactor + 0xF00, 0, 0, 0);
            }
            break;
        case 7: {
            LO *ploFocus = PloTarget(p);
            SetControl(p->pactor, 0);
            Notify(ploFocus, p->pactor);
            break;
        }
        case 8:
            switch (p->state) {
            case 7:
                if (FAsegaRetracted(p->pactor->pasega))
                    SetInteractState(p, 9);
                break;
            case 8:
                if (FAsegaRetracted(p->pactor->pasega))
                    SetControl(p->pactor, 0);
                break;
            default:
                ProbeGround(p);
                break;
            }
            break;
        case 9:
            if (FWithin(PosOfLo(PloTarget(p)), PosOfLo(p->reach.ploEnd), D_002BF5B4)) {
                AttachReachObject(&p->reach, PloTarget(p));
                SetControl(p->pactor, 0);
            }
            break;
        case 10:
            if (!p->pactor->pasega || FAsegaRetracted(p->pactor->pasega)) {
                SetControl(p->pactor, 0);
            } else if (D_002BF5B8 < g_clock.t - p->tBegin) {
                if (0.0f < p->pactor->pctl->sLeft || (p->pactor->pctl->grfbtn & 0xD0)) {
                    SetControl(p->pactor, 0);
                    return;
                }
            }
            break;
        case 11:
        case 12:
            if (!p->pactor->pasega || FAsegaRetracted(p->pactor->pasega))
                SetControl(p->pactor, 0);
            break;
        case 5:
            if (FIsBasicDerivedFrom(PloTarget(p), CID_PIPE) && FActorPoseDone(p->pactor)) {
                p->pactor->ploClimb = (LO *)p->ploTarget;
                p->pactor->sClimb = p->sTarget;
                SetControl(p->pactor, 8);
            }
            break;
        case 2:
            if (NActorPower__FP5ACTOR(p->pactor) <= 0) {
                SetControl(p->pactor, 0);
                break;
            }
            if (p->pactor->nTargetKind == 4) {
                SetControl(p->pactor, 0);
                break;
            }
            if (g_grfusr & 1)
                break;
            if (pctl->grfbtn & GrfAbilityButton__FP5ACTORi(p->pactor, 0x28))
                break;
            SetControl(p->pactor, 0);
            break;
        default:
            if (GrfPadctlTakePressed(pctl, 0x40, 0.1f)) {
                SetJumpKind(&p->pactor->jump, 1, 0, 0);
                break;
            }
            if (GrfPadctlPressedWithin(pctl, 0x400, 0.15f) && CanAct(p->pactor, 3) && (p->kind == 0 || p->kind == 13)) {
                ForgetPadctlPresses(pctl, 0x400);
                OpenBinoc((char *)p->pactor + 0xF00, 0, 0, 0);
                break;
            }
            if (p->f500)
                break;
            if (g_grfusr & 1)
                break;
            if (pctl->grfbtn & 0x20)
                break;
            SetControl(p->pactor, 0);
            break;
        }
    } while (p->state != state && p->state != -1);
}

#define FIELD_OFFSET(t, m) ((unsigned int)&(((t *)0x10000)->m) - 0x10000)
typedef char LSG_Size[sizeof(LSG) == 0x60 ? 1 : -1];
typedef char BSP_Size[sizeof(BSP) == 12 ? 1 : -1];
typedef char SOPART_absp_Offset[FIELD_OFFSET(SOPART, bspc.absp) == 0x74 ? 1 : -1];
typedef char SOPART_geomWorld_Offset[FIELD_OFFSET(SOPART, geomWorld) == 0x90 ? 1 : -1];
