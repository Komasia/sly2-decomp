/* func_00203670 (0x203670): PHOTOTARGET message handler: the base handler, then on message 0x11 (its task changed)
 * the current player's photo prompt (ACTOR +0xF38, actors only: cid 0x34) relists the targets and their marks. */
#include "cid.h"
struct SW;
extern struct SW g_sw;
struct PLAYERACTOR { char pad[0xF38]; void *pphotoprompt; };
void func_00133590(void *ptarget, int msg, void *pv);
struct PLAYERACTOR *PloPlayerPo__FP2SW(struct SW *psw);
int FIsBasicDerivedFrom__FP5BASIC3CID(void *pbasic, int cid);
void func_00202030(void *pphotoprompt);   /* lists the targets (SafeHouse: List) */
void ListMarks__FP11PHOTOPROMPT(void *pphotoprompt);

#define MSG_TaskChanged 0x11

void func_00203670(void *ptarget, int msg, void *pv)
{
    struct PLAYERACTOR *pactor;
    func_00133590(ptarget, msg, pv);
    if (msg != MSG_TaskChanged) return;
    pactor = PloPlayerPo__FP2SW(&g_sw);
    if (pactor && FIsBasicDerivedFrom__FP5BASIC3CID(pactor, CID_ACTOR) && pactor->pphotoprompt) {
        func_00202030(pactor->pphotoprompt);
        ListMarks__FP11PHOTOPROMPT(pactor->pphotoprompt);
    }
}
