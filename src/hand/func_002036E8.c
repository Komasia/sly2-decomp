/* func_002036E8 (0x2036E8): marks a photo target taken: with a task, the task is asked for state 2 (done) and the
 * player actor's binocucom window (+0xF24) refreshes its args; without one the target's own done flag is set. */
#include "h6_photo.h"
struct SW;
extern struct SW g_sw;
void RequestTaskState__FP4TASKii(PHOTOTASK *ptask, int state, PHOTOTARGET *ptarget);
char *PloPlayerPo__FP2SW(struct SW *psw);
int FIsBasicDerivedFrom__FP5BASIC3CID(void *pbasic, int cid);
void SetBinocWindowArgs__FP8BINOCWIN(void *pbinocwin);

#define CID_ACTOR 0x34
#define OFS_ACTOR_BINOCWIN 0xF24

void func_002036E8(PHOTOTARGET *ptarget, int fDone)
{
    if (ptarget->ptask) {
        char *pactor;
        RequestTaskState__FP4TASKii(ptarget->ptask, 2, ptarget);
        pactor = PloPlayerPo__FP2SW(&g_sw);
        if (pactor && FIsBasicDerivedFrom__FP5BASIC3CID(pactor, CID_ACTOR)) SetBinocWindowArgs__FP8BINOCWIN(pactor + OFS_ACTOR_BINOCWIN);
    } else ptarget->fDone = fDone;
}
