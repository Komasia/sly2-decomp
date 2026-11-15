/* StartJob: a job's start (vt slot 15): after PostLoLoad, a job not yet current shows its "end" objects and goals;
 * its play count and time come from the progress, then its +0xA8 record and its screen objects (oidScreen, 0x379) are found. */
#include "h2_task.h"
typedef struct CRef { int m_tagk; int m_tag; } CRef;
extern char D_003D4A60[];
struct SW { char pad[0x3A18]; char unk_0x3a18[0x10]; };
extern struct SW g_sw;
void PostLoLoad__FP2LO(JOB *pjob);
int FJobCur__FP3JOB(JOB *pjob);
int func_00162670(JOB *pjob);
void ApplyTaskObjects__FPviiT0(JOB *pjob, int nState, int cobje, TASKOBJE *aobje);
void ApplyTaskSms__FPvT0iT0i(JOB *pjob, int nState, int csme, TASKSME *asme, int nMode);
void NProgress(CRef *pref, PROGREF *ppr, void *pv);
void Decref(CRef *pref) asm("Decref__4CRef");
void *func_001D7E80(void *pv, PROGREF *ppr, void *pvCtx);
void *PloFindSwNearest__FP2LO3OIDii(void *psw, int grf, int oid, void *ploCtx);
// name: SafeHouse port (StartJob)
void StartJob__FP2SW(JOB *pjob)
{
    CRef ref;
    PROGREF *ppr;
    PostLoLoad__FP2LO(pjob);
    if (!FJobCur__FP3JOB(pjob) && func_00162670(pjob)) {
        ApplyTaskObjects__FPviiT0(pjob, TASKS_End, pjob->cobje, pjob->aobje);
        ApplyTaskSms__FPvT0iT0i(pjob, TASKS_End, pjob->csme, pjob->asme, 1);
    }
    ppr = &pjob->prPlayed;
    if (ppr->ckey) {
        int cPlayed;
        NProgress(&ref, ppr, D_003D4A60);
        cPlayed = ref.m_tag;
        Decref(&ref);
        pjob->cPlayed = cPlayed;
    }
    ppr = &pjob->prElapsed;
    if (ppr->ckey) {
        float tElapsed;
        NProgress(&ref, ppr, D_003D4A60);
        tElapsed = *(float *)&ref.m_tag;
        Decref(&ref);
        pjob->tElapsed = tElapsed;
    }
    pjob->pvA8 = func_001D7E80(g_sw.unk_0x3a18, &pjob->prE8, D_003D4A60);
    if (pjob->oidScreen != -1)
        pjob->ploScreen = PloFindSwNearest__FP2LO3OIDii(&g_sw, 0x405, pjob->oidScreen, 0);
    pjob->ploScreen379 = PloFindSwNearest__FP2LO3OIDii(&g_sw, 0x405, 0x379, 0);
}
