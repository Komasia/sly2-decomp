/* ApplyAsegParams (queued by PostAsegLoad through a deferred call): the ASEG applies itself with its apply
 * parameters (EOPID 107 {t, svt, grfapl}). Layout: SafeHouse port (sm.h ASEG tApply / svtApply / grfApply). */
typedef struct APPLY { float t; float svt; int grfapl; } APPLY;
void ApplyAseg__FP4ASEGiiffPP5ASEGA(void *paseg, float t, float svt, int palo, int grfapl, int ppasega);
// name: SafeHouse port (asega.cpp: "0x149A50 queues ApplyAsegParams 0x12F8C0")
void ApplyAsegParams(void *paseg, APPLY *papply) asm("ApplyAsegParams__FP4ASEGPv");
void ApplyAsegParams(void *paseg, APPLY *papply)
{
    ApplyAseg__FP4ASEGiiffPP5ASEGA(paseg, papply->t, papply->svt, 0, papply->grfapl, 0);
}
