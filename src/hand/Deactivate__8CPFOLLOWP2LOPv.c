/* CPFOLLOW::Deactivate: the follow camera policy forgets its zone and zone entry, then the base deactivate.
 * Layout: SafeHouse port (cplcy.h CPFOLLOW). */
struct LO;
struct ZONECM;
struct ZONECME;
struct CPFOLLOW {
    /* 0x00 */ char pad0[0x10];             /* the CPLCY base */
    /* 0x10 */ struct ZONECM *pzone;        /* field: SafeHouse port */
    /* 0x14 */ struct ZONECME *pcme;        /* field: SafeHouse port */
};
void DeactivateCplcy(struct CPFOLLOW *pcplcy, struct LO *plo, void *pv) asm("Deactivate__5CPLCYP2LOPv");

// name: SafeHouse port (CPFOLLOW::Deactivate)
void Deactivate__8CPFOLLOWP2LOPv(struct CPFOLLOW *pcplcy, struct LO *plo, void *pv)
{
    pcplcy->pzone = 0;
    pcplcy->pcme = 0;
    DeactivateCplcy(pcplcy, plo, pv);
}
