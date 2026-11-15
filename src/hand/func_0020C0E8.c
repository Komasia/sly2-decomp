#include "cid.h"
#include "h6_guard.h"
/* the object: its floor contact (STEP::pxpFloor) and, for a guard, its ground watcher A */
struct ALOG { char pad[0x208]; int pxpFloor; char pad2[0x498 - 0x20C]; void *pwatchA; };
struct K2PLAY { char pad[0x10]; int st; float tSt; char pad2[0x34 - 0x18]; struct ALOG *palo; int pasega; char pad3[0x50 - 0x3C]; float tArrive; float tEnd; char pad4[0x60 - 0x58]; int fBallistic; };
extern struct { float t; float dt; } g_clock;
extern float D_002C3DE0;   /* the longest fall after the arrival */
void SetK2State__FP6K2PLAYi(struct K2PLAY *pk2play, int st);
int FIsBasicDerivedFrom__FP5BASIC3CID(struct ALOG *pbasic, int cid);
void func_0020D1A0(void *pwatchA);
int FAsegaRetracted(int pasega) asm("FAsegaRetracted__FP5ASEGA");

/* UpdateK2 (0x20C0E8): the kind-2 player's state changes (repeated until it settles): in the air, a floor contact
 * 0.15 s after the start lands it, the end time makes it fall; falling, a floor or D_002C3DE0 past the arrival lands
 * it, the arrival makes a ballistic one land or a guard's ground watcher A update; landed, done once its ASEGA is
 * retracted. Field names: SafeHouse port (guard.h K2PLAY). */
// name: SafeHouse port (UpdateK2)
void UpdateK2__FP6K2PLAY(struct K2PLAY *pk2play)
{
    int st;
    do {
        st = pk2play->st;
        switch (st) {
        case K2ST_Air:
            if (pk2play->palo->pxpFloor && pk2play->tSt + 0.15f < g_clock.t)
                SetK2State__FP6K2PLAYi(pk2play, K2ST_Land);
            else if (pk2play->tEnd <= g_clock.t)
                SetK2State__FP6K2PLAYi(pk2play, K2ST_Fall);
            break;
        case K2ST_Fall:
            if (pk2play->palo->pxpFloor || g_clock.t - pk2play->tArrive > D_002C3DE0)
                SetK2State__FP6K2PLAYi(pk2play, K2ST_Land);
            else if (pk2play->tArrive <= g_clock.t) {
                if (pk2play->fBallistic)
                    SetK2State__FP6K2PLAYi(pk2play, K2ST_Land);
                else if (FIsBasicDerivedFrom__FP5BASIC3CID(pk2play->palo, CID_STEPGUARD))
                    func_0020D1A0(pk2play->palo->pwatchA);
            }
            break;
        case K2ST_Land:
            if (FAsegaRetracted(pk2play->pasega))
                SetK2State__FP6K2PLAYi(pk2play, K2ST_Done);
            break;
        }
    } while (st != pk2play->st);
}
