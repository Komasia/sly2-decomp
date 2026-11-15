struct PLAYV { char pad[0x30]; int fActive; };
struct KINDE { int k; int plo; struct PLAYV *pvState; };
int FAsegaRetracted(struct PLAYV *pplay) asm("FAsegaRetracted__FP5ASEGA");
int FSmaRetracted(struct PLAYV *pplay) asm("FSmaRetracted__FP3SMA");
int FK2Done(struct PLAYV *pplay) asm("FK2Done__FP6K2PLAY");
int FK3Done(struct PLAYV *pplay) asm("FK3Done__FP6K3PLAY");
/* FKindeDone (0x209430): whether what plays a guard kind entry is done (nothing plays, it is retracted / done, or
 * the SMA is no longer active); an empty entry is always done. */
// name: SafeHouse port (FKindeDone)
int FKindeDone__FP5KINDE(struct KINDE *pkinde)
{
    int fDone;
    switch (pkinde->k) {
    case 0:
        fDone = 0;
        if (!pkinde->pvState || FAsegaRetracted(pkinde->pvState))
            fDone = 1;
        break;
    case 1:
        fDone = 0;
        if (!pkinde->pvState || FSmaRetracted(pkinde->pvState) || !pkinde->pvState->fActive)
            fDone = 1;
        break;
    case 2:
        fDone = 0;
        if (!pkinde->pvState || FK2Done(pkinde->pvState))
            fDone = 1;
        break;
    case 3:
        fDone = 0;
        if (!pkinde->pvState || FK3Done(pkinde->pvState))
            fDone = 1;
        break;
    case -1:
    default:
        fDone = 1;
        break;
    }
    return fDone;
}
