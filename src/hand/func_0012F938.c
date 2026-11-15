/* PeventLaunch: an ASEG's timed event of kind 11 (launch) whose word is n, or null. Layout: SafeHouse port. */
typedef struct ASEGEV { int t; int kind; int n; int b; } ASEGEV;   /* field: SafeHouse port */
typedef struct ASEG { char pad[0xA0]; int cevTimed; ASEGEV *aevTimed; } ASEG;
#define ASEGEVK_Launch 0xB
// name: SafeHouse port (PeventLaunch)
ASEGEV *PeventLaunch__FP5KINDEi(ASEG *paseg, int n)
{
    int iev;
    ASEGEV *pev;
    for (iev = 0; iev < paseg->cevTimed; iev++) {
        pev = &paseg->aevTimed[iev];
        if ((pev->kind == ASEGEVK_Launch) & (pev->n == n))
            return pev;
    }
    return 0;
}
