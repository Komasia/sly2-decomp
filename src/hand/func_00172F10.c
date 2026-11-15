typedef int qword __attribute__((mode(TI)));
#include "clock.h"
extern float D_002A53D4;
struct GOAL { qword a, b; };
struct WAYPOS { qword pos; qword pad; };
struct JOBINVESTIGATE { char pad[0x18]; void *pchild; char pad2[0x20]; float tSearch; char pad3[0x10]; struct WAYPOS aposWay[4]; unsigned int iway; };
int NArrived__7JOBGOTO(void *pjob);
void func_002562A8(struct GOAL *pq);
void SetGoal__7JOBGOTOP4GOAL(void *pjob, struct GOAL *pq);
/* JOBINVESTIGATE::NextSearchPlace: once the go-to arrived and a second passed, go to the next of the four search
 * places (cycling). */
// name: SafeHouse port (JOBINVESTIGATE::NextSearchPlace)
void NextSearchPlace__14JOBINVESTIGATE(struct JOBINVESTIGATE *pjob) {
    void *pchild;
    struct WAYPOS *pway;
    struct GOAL goal;
    if (pjob->iway >= 4) return;
    pchild = pjob->pchild;
    if (pjob->tSearch == D_002A53D4) {
        if (NArrived__7JOBGOTO(pchild)) pjob->tSearch = g_clock.t + 1.0f;
    }
    if (g_clock.t < pjob->tSearch) return;
    pway = &pjob->aposWay[pjob->iway++];
    if (pjob->iway >= 4) pjob->iway = 0;
    func_002562A8(&goal);
    goal.b = pway->pos;
    SetGoal__7JOBGOTOP4GOAL(pchild, &goal);
    pjob->tSearch = D_002A53D4;
}
