/* PentFromDz: the response entry (DZENT, 0x60 bytes) of a row (DZ, 40 bytes) of a constraint system: the entry at
 * the row's index. DZG layout: SafeHouse port (dzg.h). */
struct DZ { char ab[40]; };
struct DZENT { char ab[0x60]; };
struct DZG {
    /* 0x00 */ int cdzMax;           /* field: SafeHouse port */
    /* 0x04 */ int cdz;              /* field: SafeHouse port */
    /* 0x08 */ struct DZ *adz;       /* field: SafeHouse port - the rows */
    /* 0x0c */ char padC[0x60 - 0x0c];
    /* 0x60 */ struct DZENT *aent;   /* field: SafeHouse port - the rows' responses */
};

// name: SafeHouse port (PentFromDz)
struct DZENT *PentFromDz__FP3DZGP2DZ(struct DZG *pdzg, struct DZ *pdz)
{
    return &pdzg->aent[pdz - pdzg->adz];
}
