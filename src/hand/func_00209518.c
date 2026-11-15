struct ASEGA;
/* what plays an entry, by kind: an SMA (its ASEGA at +0x30), the KIND2 player (+0x38) or the KIND3 player (+0x24) */
struct K2PLAYQ {
    char pad[0x24];
    struct ASEGA *pasegaK3;
    char pad2[8];
    struct ASEGA *pasegaSm;
    int pad3;
    struct ASEGA *pasegaK2;
};
struct KINDE { int k; int plo; struct K2PLAYQ *pvState; };

/* PasegaOfKinde (0x209518): the ASEGA playing a guard kind entry: the entry's own for an ASEG, its SMA's or its
 * KIND2 / KIND3 player's otherwise. */
// name: SafeHouse port (PasegaOfKinde)
struct ASEGA *PasegaOfKinde__FP5KINDE(struct KINDE *pkinde)
{
    switch (pkinde->k) {
    case 0: return /* ASEG */ (struct ASEGA *)pkinde->pvState;
    case 1: return /* SM */ pkinde->pvState->pasegaSm;
    case 2: return /* KIND2 */ pkinde->pvState->pasegaK2;
    case 3: return /* KIND3 */ pkinde->pvState->pasegaK3;
    }
    return 0;
}
