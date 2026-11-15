/* OnBootyXpNew: the base (0x1F4FB0); a thrown booty (5) touching anything but an actor queues its return (D_002A4B58,
 * a deferred call). */
#include "cid.h"
struct PFN8 { int a; int b; };   /* a pointer to function */
extern struct PFN8 D_002A4B58;
extern char g_sw[];
struct XPD { int psoe; int f4; int palo; char pad[0x34]; };   /* a contact end (0x40 bytes) */
struct BOOTY { char pad[0x184]; int state; };
void func_001F4FB0(struct BOOTY *, struct XPD *, int);
int FIsBasicDerivedFrom__FP5BASIC3CID(int, int);
void PostDeferredCall__FPvUi15PFNDEFERREDCALLi(void *, void *, struct PFN8, int);
// name: SafeHouse port (OnBootyXpNew)
void OnBootyXpNew__FP3ALOP2XPi(struct BOOTY *pbooty, struct XPD *axpd, int ixpd) {
    func_001F4FB0(pbooty, axpd, ixpd);
    if (pbooty->state == 5) { struct XPD *pxpd = &axpd[1 - ixpd]; if (!FIsBasicDerivedFrom__FP5BASIC3CID(pxpd->palo, CID_ACTOR)) PostDeferredCall__FPvUi15PFNDEFERREDCALLi(g_sw, pbooty, D_002A4B58, 0); }
}
