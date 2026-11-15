typedef struct DETENTRY { int an[4]; } DETENTRY;
struct DETECTOR { char pad[0xFC]; int cdetentry; DETENTRY adetentry[1]; };
struct GUARD { char pad[0x3A4]; int cdetentryGenerated; char p2[0xF64 - 0x3A8]; struct DETECTOR *pdet; };
DETENTRY *PdetentryFind__FP8DETECTORi(struct DETECTOR *pdet);
void CopyAb(void *pvDst, void *pvSrc, int cb) asm("CopyAb__FPvT0Ui");
/* func_00208860 (0x208860): removes the guard's own (not generated) detector entry for the found object (the entry
 * PdetentryFind gives), closing up the list. */
void func_00208860(struct GUARD *pguard)
{
    DETENTRY *pdetentry = PdetentryFind__FP8DETECTORi(pguard->pdet);
    struct DETECTOR *pdet = pguard->pdet;
    int cdetentry = pdet->cdetentry;
    DETENTRY *pdetentryGenerated = &pdet->adetentry[cdetentry - pguard->cdetentryGenerated];
    if (pdetentry && pdetentry < pdetentryGenerated) {
        int idetentry;
        pdet->cdetentry = cdetentry - 1;
        idetentry = pdetentry - pdet->adetentry;
        CopyAb(pdetentry, pdetentry + 1, (pguard->pdet->cdetentry - idetentry) * 16);
    }
}
