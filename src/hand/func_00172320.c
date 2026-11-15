typedef int qword __attribute__((mode(TI)));
#include "clock.h"
#include "vtbl.h"
#include "cid.h"
extern float D_002A5398;
struct GOAL { qword a; qword pos; };
struct AIJOBV { char pad[0xC]; VTENT *vt; char pad2[0x2C]; int nAnim; char pad3[0xC0 - 0x40]; int fRun; };
struct GUARD { char pad[0xFD0]; char moveref[4]; };
struct JOBINVESTIGATE { char pad[0x10]; struct GUARD *pguard; int pad2; char pchild[0x18]; int st; float tSt; float tEnd; char pad3[0xC]; int fNew; };
void EndChildJob__FPP5AIJOB(void *ppjob);
struct AIJOBV *func_00205438(void *pguard, int cid);   /* the guard's job of a class */
qword PosNoise__14JOBINVESTIGATE(struct JOBINVESTIGATE *pjob);
qword PosOfLo__FP2LO(void *plo);
void func_002562A8(struct GOAL *x);
void SetGoal__7JOBGOTOP4GOAL(void *pjob, struct GOAL *x);
float atan2f(float y, float x);
void SetMoveHeading__FP7MOVEREF(void *pmoveref, float f);
void SetDeadlines__14JOBINVESTIGATE(struct JOBINVESTIGATE *pjob);
void FindSearchPlaces__14JOBINVESTIGATE(struct JOBINVESTIGATE *pjob);
void NextSearchPlace__14JOBINVESTIGATE(struct JOBINVESTIGATE *pjob);
void SetNoise__14JOBINVESTIGATEP5NOISE(struct JOBINVESTIGATE *pjob, int pnoise);
static __inline__ float GetX(qword q) { float x; __asm__("mtc1 %1,%0" : "=f"(x) : "r"(q)); return x; }
static __inline__ float GetY(qword q) { float y; __asm__("prot3w %0,%1" : "=r"(y) : "r"(q)); return y; }
/* JOBINVESTIGATE::SetInvestigateState: leave the state's child job and start the new one: alerted (a move,
 * animation 12), going (a go-to the noise, with a deadline), looking (face the noise, a stand, the deadlines),
 * searching (a go-to over the search places), giving up (a move, animation 14, the noise dropped), paused (a stand). */
// name: SafeHouse port (JOBINVESTIGATE::SetInvestigateState)
void SetInvestigateState__14JOBINVESTIGATEi(struct JOBINVESTIGATE *pjob, int stNew) {
    if (stNew == pjob->st) return;
    EndChildJob__FPP5AIJOB(pjob->pchild);
    pjob->st = stNew;
    pjob->tSt = g_clock.t;
    switch (stNew) {
    case 0:
        { struct AIJOBV *pjobChild = func_00205438(pjob->pguard, CID_JOBMOVE); VTENT *pvte; pjobChild->nAnim = 0xC; pvte = &pjobChild->vt[8]; ((void (*)(void *))pvte->pfn)(VT_THIS(pjobChild, pvte)); }
        break;
    case 1:
        {
            struct AIJOBV *pjobChild = func_00205438(pjob->pguard, CID_JOBGOTO);
            struct GOAL x;
            VTENT *pvte;
            qword pos;
            pjobChild->fRun = 1;
            pos = PosNoise__14JOBINVESTIGATE(pjob);
            func_002562A8(&x);
            x.pos = pos;
            SetGoal__7JOBGOTOP4GOAL(pjobChild, &x);
            pvte = &pjobChild->vt[8]; ((void (*)(void *))pvte->pfn)(VT_THIS(pjobChild, pvte));
            pjob->tEnd = D_002A5398;
        }
        break;
    case 2:
        {
            qword a = PosNoise__14JOBINVESTIGATE(pjob);
            qword b = PosOfLo__FP2LO(pjob->pguard);
            qword dpos;
            __asm__("vsub.xyzw %0, %1, %2" : "=j"(dpos) : "j"(a), "j"(b));
            SetMoveHeading__FP7MOVEREF(pjob->pguard->moveref, atan2f(GetY(dpos), GetX(dpos)));
            { struct AIJOBV *pjobChild = func_00205438(pjob->pguard, CID_JOBSTAND); VTENT *pvte = &pjobChild->vt[8]; ((void (*)(void *))pvte->pfn)(VT_THIS(pjobChild, pvte)); }
            SetDeadlines__14JOBINVESTIGATE(pjob);
        }
        break;
    case 3:
        {
            struct AIJOBV *pjobChild = func_00205438(pjob->pguard, CID_JOBGOTO);
            VTENT *pvte;
            pjobChild->fRun = 1;
            FindSearchPlaces__14JOBINVESTIGATE(pjob);
            NextSearchPlace__14JOBINVESTIGATE(pjob);
            pvte = &pjobChild->vt[8]; ((void (*)(void *))pvte->pfn)(VT_THIS(pjobChild, pvte));
        }
        break;
    case 4:
        { struct AIJOBV *pjobChild = func_00205438(pjob->pguard, CID_JOBMOVE); VTENT *pvte; pjobChild->nAnim = 0xE; pvte = &pjobChild->vt[8]; ((void (*)(void *))pvte->pfn)(VT_THIS(pjobChild, pvte)); }
        SetNoise__14JOBINVESTIGATEP5NOISE(pjob, 0);
        pjob->fNew = 0;
        break;
    case 5:
        { struct AIJOBV *pjobChild = func_00205438(pjob->pguard, CID_JOBSTAND); VTENT *pvte; pjobChild->nAnim = 1; pvte = &pjobChild->vt[8]; ((void (*)(void *))pvte->pfn)(VT_THIS(pjobChild, pvte)); }
        break;
    }
}
