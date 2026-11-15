/* func_001E4F20: sets the script's current tunnel object (JSG ptnCur) to ptn: the previous one is unforced from its
 * zone, unbound, and removed again (vt slot 9) if the script added it; the new one is added (vt slot 8) when it is not
 * in the world yet (fHideTn: the script added it, so it removes it later), bound to the script's actor if that is an
 * SO (else func_001C4A48(&g_sw)), and forced into its zone. */
#include "relay.h"
#include "cid.h"
struct TN { int pad[3]; VTENT *vt; char pad2[0x28 - 0x10]; unsigned long flPad : 60; unsigned int fInWorld : 1; char pad3[0xE0 - 0x30]; void *paloBound; };
struct G { int a; };
extern struct G g_sw;
struct RUNTN { char pad[0x24]; void *ploActor; char pad2[0x6C - 0x28]; struct TN *ptnCur; int fHideTn; };   /* relay.h JSG */
void SetZoneForced__FP2LOi(struct TN *ptn, int fForced);
int FIsBasicDerivedFrom__FP5BASIC3CID(void *pbasic, int cid);
void *func_001C4A48(struct G *psw);
void func_001E4F20(struct RUNTN *pjsg, struct TN *ptn)
{
    if (pjsg->ptnCur) {
        SetZoneForced__FP2LOi(pjsg->ptnCur, -1);
        pjsg->ptnCur->paloBound = 0;
        if (pjsg->fHideTn) ((void (*)(void *))pjsg->ptnCur->vt[9].pfn)(VT_THIS(pjsg->ptnCur, &pjsg->ptnCur->vt[9]));
        pjsg->ptnCur = 0;
    }
    if (!ptn) return;
    pjsg->ptnCur = ptn;
    pjsg->fHideTn = !ptn->fInWorld;
    if (pjsg->fHideTn) ((void (*)(void *))ptn->vt[8].pfn)(VT_THIS(ptn, &ptn->vt[8]));
    ptn->paloBound = (pjsg->ploActor && FIsBasicDerivedFrom__FP5BASIC3CID(pjsg->ploActor, CID_SO)) ? pjsg->ploActor : func_001C4A48(&g_sw);
    SetZoneForced__FP2LOi(ptn, 1);
}
