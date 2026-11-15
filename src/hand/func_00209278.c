#include "vtbl.h"
/* a playing ASEGA / SMA / player: its vtable */
struct PLAYV { char pad[0xC]; VTENT *pvt; };
/* a guard kind entry (see h6_guard.h): its kind, object and what plays it */
struct KINDE { int k; int plo; struct PLAYV *pvState; };
void ApplyAseg__FP4ASEGiiffPP5ASEGA(int paseg, char *palo, int grf, struct PLAYV **ppasega, float uWeight, float uSpeed);
void func_001F0198(int psm, char *palo, int oid, int grf, struct PLAYV **ppsma);   /* PsmaApplySm */
void StartK2__FP5KIND2P3ALOiP6K2PLAY(int pk2, char *palo, int grf, struct PLAYV *pplay);
void StartK3__FP5KIND3iiP6K3PLAY(int pk3, char *palo, int grf, struct PLAYV *pplay);
#define VC1(o) /* vt slot 1 */ ((void (*)(void *))(o)->pvt[1].pfn)(VT_THIS((o), &(o)->pvt[1]))
/* PlayKinde (0x209278): starts a guard kind entry on the guard with ApplyAseg flags grf: an ASEG (weight uWeight)
 * or an SM gets its new ASEGA / SMA, a KIND2 / KIND3 starts the guard's player at +0xDB0 / +0xE20; then the
 * player's vt slot 1. */
#define OFS_GUARD_K2PLAY 0xDB0
#define OFS_GUARD_K3PLAY 0xE20
// name: SafeHouse port (PlayKinde)
void PlayKinde__FP5KINDEP5GUARDif(struct KINDE *pkinde, char *pguard, int grf, float uWeight)
{
    switch (pkinde->k) {
    case -1: /* none */
        break;
    case 0: /* ASEG */
        ApplyAseg__FP4ASEGiiffPP5ASEGA(pkinde->plo, pguard, grf, &pkinde->pvState, uWeight, 1.0f);
        VC1(pkinde->pvState);
        break;
    case 1: /* SM */
        func_001F0198(pkinde->plo, pguard, -1, grf, &pkinde->pvState);
        VC1(pkinde->pvState);
        break;
    case 2: /* KIND2 */
        pkinde->pvState = (struct PLAYV *)(pguard + OFS_GUARD_K2PLAY);
        StartK2__FP5KIND2P3ALOiP6K2PLAY(pkinde->plo, pguard, grf, pkinde->pvState);
        VC1(pkinde->pvState);
        break;
    case 3: /* KIND3 */
        pkinde->pvState = (struct PLAYV *)(pguard + OFS_GUARD_K3PLAY);
        StartK3__FP5KIND3iiP6K3PLAY(pkinde->plo, pguard, grf, pkinde->pvState);
        VC1(pkinde->pvState);
        break;
    }
}
