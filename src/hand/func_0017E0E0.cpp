/* JOBBD::ChooseAway: the point to run to: of 16 directions around the one from the object to the guard (at a fixed
 * distance), the one kept on the navigation that is farthest from the object (else the current goal); set as the
 * JOBGOTO child's goal. */
typedef int qword __attribute__((mode(TI)));
struct GOAL;
extern "C" {
#include "clock.h"
extern float D_002BE76C;        /* the distance tried */
extern float D_002BE770[16];    /* the directions' angles */
/* GOAL (SafeHouse aijobs.h): constructed cleared */
struct GOAL { qword a; qword pos; GOAL(); };
struct JOBGOTO { char pad0[0x40]; struct GOAL goal; };
struct NAV { char pad0[0x10]; void *pnavregion; };
struct SOPHYS { char pad0[0xDC]; struct NAV *pnav; };
struct GUARD { char pad0[0xE8]; struct SOPHYS *pE8; };
struct JOBBD {
    /* 0x00 */ char pad0[0x10];
    /* 0x10 */ struct GUARD *pguard;
    /* 0x14 */ int pad14;
    /* 0x18 */ struct JOBGOTO *pjobGoto;   /* the child job */
    /* 0x1c */ char pad1C[0x38 - 0x1C];
    /* 0x38 */ void *ploFrom;              /* field: SafeHouse port */
    /* 0x3c */ float tChoose;              /* field: SafeHouse port */
};
qword PosOfLo(void *plo) asm("PosOfLo__FP2LO");
float atan2f(float y, float x) asm("atan2f");
qword PosGoal(struct GOAL *pgoal, qword posFrom) asm("PosGoal__FP4GOALG9VU_VECTOR");
qword SetVectorCylind(float rad, float r, float z) asm("SetVectorCylind__Ffff");
int FKeepOnNav(void *pnavregion, qword pos, qword *ppos) asm("FKeepOnNav__FP9NAVREGIONG9VU_VECTORP6VECTOR");
void func_002562A8(struct GOAL *pgoal);   /* the goal cleared */
void SetGoal(void *pjobGoto, struct GOAL *pgoal) asm("SetGoal__7JOBGOTOP4GOAL");
}
inline GOAL::GOAL() { func_002562A8(this); }
static __inline__ float GetX(qword q) { float x; __asm__("mtc1 %1,%0" : "=f"(x) : "r"(q)); return x; }
static __inline__ float GetY(qword q) { float y; __asm__("prot3w %0,%1" : "=r"(y) : "r"(q)); return y; }

// name: SafeHouse port (JOBBD::ChooseAway)
extern "C" void ChooseAway__5JOBBD(struct JOBBD *pjob) {
    union { qword q; } posKept;
    qword posFrom, posGuard, dpos, posBest;
    struct JOBGOTO *pjobGoto;
    struct SOPHYS *psophys;
    struct NAV *pnav;
    void *pnavregion;
    float rad, distBest;
    unsigned int i;
    pjob->tChoose = g_clock.t;
    pjobGoto = pjob->pjobGoto;
    posFrom = PosOfLo(pjob->ploFrom);
    posGuard = PosOfLo(pjob->pguard);
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(dpos) : "j"(posGuard), "j"(posFrom));
    psophys = pjob->pguard->pE8;
    pnav = psophys ? psophys->pnav : 0;
    pnavregion = pnav ? pnav->pnavregion : 0;
    distBest = 0.0f;
    rad = atan2f(GetY(dpos), GetX(dpos));
    posBest = PosGoal(&pjobGoto->goal, posGuard);
    for (i = 0; i < 16; i++) {
        qword dposTry = SetVectorCylind(rad + D_002BE770[i], D_002BE76C, 0.0f);
        qword posTry;
        __asm__("vadd.xyzw %0, %1, %2" : "=j"(posTry) : "j"(posGuard), "j"(dposTry));
        if (FKeepOnNav(pnavregion, posTry, &posKept.q)) {
            qword d, l;
            float dist;
            __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(posKept.q), "j"(posFrom));
            __asm__("vmul.xy %0, %1, %1\n\tvaddy.x %0, %0, %0y" : "=j"(d) : "j"(d));
            __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(l) : "j"(d));
            __asm__("qmfc2.ni %0, %1" : "=r"(dist) : "j"(l));
            if (dist > distBest) {
                distBest = dist;
                posBest = posKept.q;
            }
        }
    }
    struct GOAL goal;
    goal.pos = posBest;
    SetGoal(pjobGoto, &goal);
}
