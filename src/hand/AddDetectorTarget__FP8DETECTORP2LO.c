/* AddDetectorTarget: an object watched by a detector (once; at most 8 entries of 16 bytes at +0x100), its entry in
 * state 0. Layout: SafeHouse port (detect.h DETECTOR, DETENTRY). */
struct LO;
struct DETENTRY {
    /* 0x0 */ struct LO *plo;   /* field: SafeHouse port */
    /* 0x4 */ char pad4[0x10 - 0x4];
};
struct DETECTOR {
    /* 0x000 */ char pad0[0xfc];
    /* 0x0fc */ unsigned int cdetentry;      /* field: SafeHouse port */
    /* 0x100 */ struct DETENTRY adetentry[8];   /* field: SafeHouse port */
};
struct DETENTRY *PdetentryFind__FP8DETECTORi(struct DETECTOR *pdet, struct LO *plo);
void SetDetentryState__FP8DETECTORP8DETENTRYi(struct DETECTOR *pdet, struct DETENTRY *pdetentry, int st);

// name: SafeHouse port (AddDetectorTarget)
void AddDetectorTarget__FP8DETECTORP2LO(struct DETECTOR *pdet, struct LO *plo)
{
    if (PdetentryFind__FP8DETECTORi(pdet, plo) == 0) {
        unsigned int c = pdet->cdetentry;
        if (c < 8) {
            struct DETENTRY *pdetentry;
            pdet->cdetentry = c + 1;
            pdetentry = &pdet->adetentry[c];
            pdetentry->plo = plo;
            SetDetentryState__FP8DETECTORP8DETENTRYi(pdet, pdetentry, 0);
        }
    }
}
