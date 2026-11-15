typedef int qword __attribute__((mode(TI)));
struct XFX { char pad[0xA0]; int pxf; };
struct ALOX { char pad[0x58]; struct XFX *pxfPos; };
struct CTRLTARGET { char pad[0x20]; qword posGoal; };   /* the ballistic flight's target controller */
struct K2PLAY { char pad[0x10]; int st; char pad2[0x20]; struct ALOX *palo; char pad3[8]; qword posTarget; char pad4[0x10]; int fBallistic; int pad5; struct CTRLTARGET *pctrl; };
qword PosConvertXfs__FP2XFT0G9VU_VECTOR(int pxfFrom, int pxfTo, qword pos);
/* SetK2Target (0x20C6F8): the kind-2 player's target: before the flight it is kept; in the air or falling a ballistic
 * flight's controller is aimed at it (in the object's position record's frame). */
#include "h6_guard.h"
// name: SafeHouse port (SetK2Target)
void SetK2Target__FP6K2PLAYG9VU_VECTOR(struct K2PLAY *pk2play, qword posTarget)
{
    switch (pk2play->st) {
    case K2ST_Start: pk2play->posTarget = posTarget; break;
    case K2ST_Air: case K2ST_Fall:
        if (pk2play->fBallistic) { struct CTRLTARGET *pctrl = pk2play->pctrl; pctrl->posGoal = PosConvertXfs__FP2XFT0G9VU_VECTOR(0, pk2play->palo->pxfPos->pxf, posTarget); }
        break;
    }
}
