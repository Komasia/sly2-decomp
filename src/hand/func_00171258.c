/* JOBSCRIPT::SetTarget: switch the job to another command list: the old one's child job ended, message 3, its frame
 * and sidebag dropped and its state cleared; then the new list's frame, message 2, the run flag, and the cursor at its
 * first command (or the saved place) executed (vt slot 15). */
#include "vtbl.h"
struct JOBSCRIPT;
struct CMDLIST { int pframe; char pad[0x4C]; int pcmdFirst; };   /* CMDLIST */
struct SAVEDSCRIPT { int pcmd; int plo; };                         /* SAVEDSCRIPT */
/* JOBSCRIPT (include/h2_aijobs.h) */
struct JOBSCRIPT { int pad0; char psidebag[8]; VTENT *vt; char pad[8]; char pchild[0x18]; struct CMDLIST *pcmdlist; int ploNear; int pcmd; int pad3; int fRunning; struct SAVEDSCRIPT *psaved; int pad4; int fFromReact; };
void EndChildJob__FPP5AIJOB(void *pjob);
void func_00256EE0(struct JOBSCRIPT *pjob, int n);
void func_002580A8(void *pjob, int n);
// name: SafeHouse port (JOBSCRIPT::SetTarget)
void SetTarget__9JOBSCRIPTP7CMDLISTiP11SAVEDSCRIPT(struct JOBSCRIPT *pjob, struct CMDLIST *pcmdlistNew, int fFromReact, struct SAVEDSCRIPT *psavedNew) {
    if (pcmdlistNew == pjob->pcmdlist) return;
    if (pjob->pcmdlist) {
        EndChildJob__FPP5AIJOB(pjob->pchild);
        ((void (*)())pjob->vt[3].pfn)(VT_THIS(pjob, &pjob->vt[3]), 3, 0, 0, 0, 0);
        func_00256EE0(pjob, 0);
        func_002580A8(pjob->psidebag, 0);
        pjob->ploNear = 0;
        pjob->pcmd = 0;
        pjob->fRunning = 0;
        pjob->fFromReact = 0;
    }
    pjob->pcmdlist = pcmdlistNew;
    if (!pcmdlistNew) return;
    func_00256EE0(pjob, pcmdlistNew->pframe);
    ((void (*)())pjob->vt[3].pfn)(VT_THIS(pjob, &pjob->vt[3]), 2, 0, 0, 0, 0);
    pjob->fFromReact = fFromReact;
    if (!psavedNew || !psavedNew->pcmd) {
        struct CMDLIST *pcmdlistT = pjob->pcmdlist;
        int n = pcmdlistT->pcmdFirst;
        pjob->ploNear = (int)pcmdlistT;
        pjob->pcmd = n;
    } else {
        pjob->pcmd = psavedNew->pcmd;
        pjob->psaved = psavedNew;
        pjob->ploNear = psavedNew->plo;
    }
    if (pjob->pcmd) ((void (*)())pjob->vt[15].pfn)(VT_THIS(pjob, &pjob->vt[15]), pjob->pcmd);
    pjob->psaved = 0;
}
