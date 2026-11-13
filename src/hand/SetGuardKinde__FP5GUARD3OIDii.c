/* SetGuardKinde (splice method 243 {indices, oid, grf}): the guard's kind entry of a list of indices gets a new
 * object (an ASEG / SM / KIND2 / KIND3 by oid, resolved later) and ApplyAseg flags. Layout: SafeHouse port
 * (guard.h KINDE). */
struct GUARD;
struct KINDE {
    /* 0x00 */ int k;      /* field: SafeHouse port (-1 none, 0 ASEG, 1 SM, 2 KIND2, 3 KIND3) */
    /* 0x04 */ int oid;    /* field: SafeHouse port - before the resolve */
    /* 0x08 */ void *pv;
    /* 0x0c */ int grf;    /* field: SafeHouse port */
};
unsigned long MaskOfList__FPv(void *plist);
struct KINDE *PkindeOfMask__FP5GUARDUl(struct GUARD *pguard, unsigned long mask);

// name: SafeHouse port (SetGuardKinde)
void SetGuardKinde__FP5GUARD3OIDii(struct GUARD *pguard, void *plistIndices, int oid, int grf)
{
    struct KINDE *pkinde = PkindeOfMask__FP5GUARDUl(pguard, MaskOfList__FPv(plistIndices));
    pkinde->oid = oid;
    pkinde->grf = grf;
}
