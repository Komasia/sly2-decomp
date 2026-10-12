typedef int OID;
typedef struct RSMG { OID oidRoot; OID oidSM; OID oidTrigger; OID oidNoTrigger; } RSMG;
int FAddRsmg(void *pv, RSMG *arsmg, int crsmgMax, int *pcrsmg, int fTrigger, OID oidRoot, OID oidSM, OID oid)
    __asm__("FAddRsmg__FP4RSMGiPii3OIDN24");
int FAddRsmg(void *pv, RSMG *arsmg, int crsmgMax, int *pcrsmg, int fTrigger, OID oidRoot, OID oidSM, OID oid)
{
    int i;
    for (i = 0; i < *pcrsmg; i++) {
        RSMG *prsmg = &arsmg[i];
        if (prsmg->oidRoot == oidRoot && (prsmg->oidSM == -1 || prsmg->oidSM == oidSM)) {
            if (fTrigger)
                prsmg->oidTrigger = oid;
            else
                prsmg->oidNoTrigger = oid;
            return 1;
        }
    }
    if (*pcrsmg + 1 >= crsmgMax)
        return 0;
    i = (*pcrsmg)++;
    arsmg[i].oidRoot = oidRoot;
    arsmg[i].oidSM = oidSM;
    if (fTrigger) {
        arsmg[i].oidTrigger = oid;
        arsmg[i].oidNoTrigger = -1;
    } else {
        arsmg[i].oidNoTrigger = oid;
        arsmg[i].oidTrigger = -1;
    }
    return 1;
}
