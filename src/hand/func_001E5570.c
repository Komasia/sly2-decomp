/* func_001E5570: when a script is cut short inside its block while its actor follows a path or walks (FollowPath /
 * WalkTo), clears the actor's jobs (+0x26C) so it stops. */
#include "relay.h"
#include "cid.h"
struct ACTORJ { char pad[0x26C]; int jobs; };
#define ACTOR_OF(pjsg) ((struct ACTORJ *)(pjsg)->ploActor)
int FIsBasicDerivedFrom__FP5BASIC3CID(struct ACTORJ *pactor, int cid);
void ClearJobs__FP5ACTOR(void *p);
void func_001E5570(JSG *pjsg)
{
    if (pjsg->prelaycmdFirst < pjsg->prelaycmdCur && pjsg->prelaycmdCur < pjsg->prelaycmdLast) {
        switch (pjsg->prelaycmdCur->relayck) {
        case RELAYCK_FollowPath:
            if (ACTOR_OF(pjsg) && FIsBasicDerivedFrom__FP5BASIC3CID(ACTOR_OF(pjsg), CID_ACTOR)) ClearJobs__FP5ACTOR(&ACTOR_OF(pjsg)->jobs);
            break;
        case RELAYCK_WalkTo:
            if (ACTOR_OF(pjsg) && FIsBasicDerivedFrom__FP5BASIC3CID(ACTOR_OF(pjsg), CID_ACTOR)) ClearJobs__FP5ACTOR(&ACTOR_OF(pjsg)->jobs);
            break;
        }
    }
}
