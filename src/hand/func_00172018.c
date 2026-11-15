#include "stepguard.h"
#include "clock.h"
struct GOAL { qword a; qword pos; };
struct JOBINVESTIGATE { char pad[0x10]; struct GUARD *pguard; int pad2; void *pchild; char pad3[0x14]; int st; float tSt; float tEnd; float tSearch; char pad4[8]; int fNew; };
void Update__5AIJOB(struct JOBINVESTIGATE *pjob);
int FJobDone(struct JOBINVESTIGATE *pjob) asm("FJobDone__FP5AIJOB");
int func_00174FB8(void *pjob);
int func_00209098(void *pguard);
int FNear__14JOBINVESTIGATE(struct JOBINVESTIGATE *pjob);
qword PosNoise__14JOBINVESTIGATE(struct JOBINVESTIGATE *pjob);
qword PosOfLo__FP2LO(void *plo);
void func_002562A8(struct GOAL *x);
void SetGoal__7JOBGOTOP4GOAL(void *pjob, struct GOAL *x);
int NArrived__7JOBGOTO(void *pjob);
int FStuck__7JOBGOTO(void *pjob);
void SetInvestigateState__14JOBINVESTIGATEi(struct JOBINVESTIGATE *pjob, int stNew);
void SetDeadlines__14JOBINVESTIGATE(struct JOBINVESTIGATE *pjob);
void NextSearchPlace__14JOBINVESTIGATE(struct JOBINVESTIGATE *pjob);
float atan2f(float y, float x);
void SetMoveHeading__FP7MOVEREF(void *pmoveref, float f);
static __inline__ float GetX(qword q) { float x; __asm__("mtc1 %1,%0" : "=f"(x) : "r"(q)); return x; }
static __inline__ float GetY(qword q) { float y; __asm__("prot3w %0,%1" : "=r"(y) : "r"(q)); return y; }
/* JOBINVESTIGATE::Update: step the investigation (repeatedly while the state changes): alerted -> going; going
 * until near / arrived / stuck -> looking (a new noise re-aims it); looking until the deadline -> giving up, or the
 * search time -> searching, else facing the noise; searching over the search places until the deadline; any state
 * but giving up pauses (5) while the game is paused; giving up ends it (-1). */
// name: SafeHouse port (JOBINVESTIGATE::Update)
void Update__14JOBINVESTIGATE(struct JOBINVESTIGATE *pjob) {
    int stOld;
    Update__5AIJOB(pjob);
    while (!FJobDone(pjob)) {
        stOld = pjob->st;
        switch (stOld) {
        case 0:
            if (func_00174FB8(pjob->pchild)) SetInvestigateState__14JOBINVESTIGATEi(pjob, 1);
            break;
        case 1:
            if (func_00209098(pjob->pguard)) {
                SetInvestigateState__14JOBINVESTIGATEi(pjob, 5);
            } else if (pjob->fNew) {
                if (FNear__14JOBINVESTIGATE(pjob)) {
                    SetInvestigateState__14JOBINVESTIGATEi(pjob, 2);
                } else {
                    qword pos = PosNoise__14JOBINVESTIGATE(pjob);
                    struct GOAL x;
                    func_002562A8(&x);
                    x.pos = pos;
                    SetGoal__7JOBGOTOP4GOAL(pjob->pchild, &x);
                }
                pjob->fNew = 0;
            } else if (FNear__14JOBINVESTIGATE(pjob) || NArrived__7JOBGOTO(pjob->pchild) || FStuck__7JOBGOTO(pjob->pchild)) {
                SetInvestigateState__14JOBINVESTIGATEi(pjob, 2);
            }
            break;
        case 2:
            if (func_00209098(pjob->pguard)) {
                SetInvestigateState__14JOBINVESTIGATEi(pjob, 5);
            } else if (pjob->fNew) {
                if (FNear__14JOBINVESTIGATE(pjob)) {
                    SetDeadlines__14JOBINVESTIGATE(pjob);
                } else {
                    SetInvestigateState__14JOBINVESTIGATEi(pjob, 1);
                }
                pjob->fNew = 0;
            } else if (pjob->tEnd < g_clock.t || func_00174FB8(pjob->pchild)) {
                SetInvestigateState__14JOBINVESTIGATEi(pjob, 4);
            } else if (g_clock.t > pjob->tSearch) {
                SetInvestigateState__14JOBINVESTIGATEi(pjob, 3);
            } else {
                qword a = PosNoise__14JOBINVESTIGATE(pjob);
                qword b = PosOfLo__FP2LO(pjob->pguard);
                qword dpos;
                __asm__("vsub.xyzw %0, %1, %2" : "=j"(dpos) : "j"(a), "j"(b));
                SetMoveHeading__FP7MOVEREF(pjob->pguard->move, atan2f(GetY(dpos), GetX(dpos)));
            }
            break;
        case 3:
            if (func_00209098(pjob->pguard)) {
                SetInvestigateState__14JOBINVESTIGATEi(pjob, 5);
            } else if (pjob->fNew) {
                if (FNear__14JOBINVESTIGATE(pjob)) {
                    SetInvestigateState__14JOBINVESTIGATEi(pjob, 2);
                } else {
                    SetInvestigateState__14JOBINVESTIGATEi(pjob, 1);
                }
                pjob->fNew = 0;
            } else if (pjob->tEnd < g_clock.t) {
                SetInvestigateState__14JOBINVESTIGATEi(pjob, 4);
            } else {
                NextSearchPlace__14JOBINVESTIGATE(pjob);
            }
            break;
        case 5:
            if (!func_00209098(pjob->pguard)) SetInvestigateState__14JOBINVESTIGATEi(pjob, 1);
            break;
        case 4:
            if (pjob->fNew) {
                if (FNear__14JOBINVESTIGATE(pjob)) {
                    SetInvestigateState__14JOBINVESTIGATEi(pjob, 2);
                } else {
                    SetInvestigateState__14JOBINVESTIGATEi(pjob, 1);
                }
                pjob->fNew = 0;
            } else if (func_00174FB8(pjob->pchild)) {
                SetInvestigateState__14JOBINVESTIGATEi(pjob, -1);
            }
            break;
        }
        if (pjob->st != stOld) continue;
        break;
    }
}
