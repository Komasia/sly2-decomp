/* func_00154158: the detection state of an object in a detector's entry list (DETENTRY +0x4), or -1 when the
 * object is not in the list. Called by the splice getters func_00104108 (a guard's detector, GUARD +0xF64) and
 * func_001042D0 (a standalone detector).
 * name: was X509v3_data_type_by_NID, a bogus OpenSSL name from a library signature match (no OpenSSL in Sly 2).
 * The SafeHouse port has no name for it, so it keeps its address name. DETENTRY layout: SafeHouse port (detect.h). */
struct DETECTOR;
struct LO;
struct DETENTRY {
    /* 0x0 */ struct LO *plo;   /* field: SafeHouse port */
    /* 0x4 */ int st;           /* field: SafeHouse port - the detection state */
};
struct DETENTRY *PdetentryFind(struct DETECTOR *pdetector, struct LO *plo) asm("PdetentryFind__FP8DETECTORi");

int func_00154158(struct DETECTOR *pdetector, struct LO *plo)
{
    struct DETENTRY *pdetentry = PdetentryFind(pdetector, plo);
    if (pdetentry)
        return pdetentry->st;
    return -1;
}
