#include "vtbl.h"
struct PLAYV { char pad[0xC]; VTENT *pvt; };
struct KINDE { int k; int plo; struct PLAYV *pvState; };
void RetractAsega__FP5ASEGA(struct PLAYV *pplay);
void RetractSma__FP3SMA(struct PLAYV *pplay);
void StopK2__FP6K2PLAY(struct PLAYV *pplay);
void StopK3__FP6K3PLAY(struct PLAYV *pplay);
#define VDEL(o) /* vt slot 2: delete */ ((void (*)(void *))(o)->pvt[2].pfn)(VT_THIS((o), &(o)->pvt[2]))
/* StopKinde (0x209360): stops what plays a guard kind entry (retracts the ASEGA / SMA, stops the KIND2 / KIND3
 * player) and deletes it (vt slot 2). */
// name: SafeHouse port (StopKinde)
void StopKinde__FP5KINDE(struct KINDE *pkinde)
{
    switch (pkinde->k) {
    case -1:
        break;
    case 0:
        if (pkinde->pvState) {
            RetractAsega__FP5ASEGA(pkinde->pvState);
            VDEL(pkinde->pvState);
            pkinde->pvState = 0;
        }
        break;
    case 1:
        if (pkinde->pvState) {
            RetractSma__FP3SMA(pkinde->pvState);
            VDEL(pkinde->pvState);
            pkinde->pvState = 0;
        }
        break;
    case 2:
        if (pkinde->pvState) {
            StopK2__FP6K2PLAY(pkinde->pvState);
            VDEL(pkinde->pvState);
            pkinde->pvState = 0;
        }
        break;
    case 3:
        if (pkinde->pvState) {
            StopK3__FP6K3PLAY(pkinde->pvState);
            VDEL(pkinde->pvState);
            pkinde->pvState = 0;
        }
        break;
    }
}
