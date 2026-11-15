/* class: the safe house, class 0x46 (SafeHouse po.cpp StepSafeHouse, orig 0x1D77D0): step the safe house's state
 * machine d states (wrapping) from its current state to the next allowed one (the list at +0x220, see
 * func_001D7780); d 0 means the current one if allowed, else the next. With no allowed state the binding is
 * released. */
typedef int OID;
typedef struct { char pad[0x50]; int csms; } SM;   /* the state machine: its state count */
typedef struct SAFEHOUSE {
    /* 0x000 */ char pad0[0x184];
    /* 0x184 */ SM *psm;
    /* 0x188 */ void *psma;           /* field: SafeHouse port */
    /* 0x18c */ char pad18c[0x220 - 0x18C];
    /* 0x220 */ int coidAllowed;
    /* 0x224 */ OID aoidAllowed[8];
} SAFEHOUSE;
OID OidSmaCur(void *psma) asm("OidSmaCur__FP3SMA");
int func_001F0438(SM *psm, OID oid);   /* the state's index */
OID OidFromSmIsms__FP2SMi(SM *psm, int isms);
void SetSmaGoal__FP3SMA3OID(void *psma, OID oid);
void ReplaceSmaHandle__FP2SMi3OIDiPP3SMA(int psm, SAFEHOUSE *psh, int oid, int n, void **ppsma);

void func_001D77D0(SAFEHOUSE *psh, int dState)
{
    int ismsStart;
    int isms;
    if (psh->psma == 0)
        return;
    isms = func_001F0438(psh->psm, OidSmaCur(psh->psma));
    ismsStart = isms;
    for (;;) {
        OID oid;
        int ioid;
        isms += dState;
        if (isms < 0)
            isms = psh->psm->csms - 1;
        else if (isms >= psh->psm->csms)
            isms = 0;
        oid = OidFromSmIsms__FP2SMi(psh->psm, isms);
        for (ioid = 0; ioid < psh->coidAllowed; ioid++) {
            if (psh->aoidAllowed[ioid] == oid) {
                SetSmaGoal__FP3SMA3OID(psh->psma, oid);
                return;
            }
        }
        if (dState == 0)
            dState = 1;
        else if (isms == ismsStart)
            break;
    }
    ReplaceSmaHandle__FP2SMi3OIDiPP3SMA(0, psh, -1, 0, &psh->psma);
}
