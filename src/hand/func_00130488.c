/* PasegaApplyAseg: ApplyAseg returning the new ASEGA. SafeHouse port (asega.h). */
void ApplyAseg__FP4ASEGiiffPP5ASEGA(int paseg, int palo, int grfapl, int *ppasega, float t, float svt);
// name: SafeHouse port (PasegaApplyAseg)
int PasegaApplyAseg__Fiiiff(int paseg, int palo, int grfapl, float t, float svt)
{
    int pasega;
    ApplyAseg__FP4ASEGiiffPP5ASEGA(paseg, palo, grfapl, &pasega, t, svt);
    return pasega;
}
