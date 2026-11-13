/* func_001800A0: add a gun to a ship (a hack/vehicle object): {the record oid its right stick turns, the state
 * machine run on the ship}, at most 4. Called by the splice method func_0010FD00 (EOPID 1371).
 * name: was UseStepguardDeathAnimation__FP9STEPGUARDi3OID, a bad Sly 1 shape match (same body shape as Sly 1's
 * "count < 4, append two words" setters); the SafeHouse port (hack.cpp: "A gun of the ship (orig +0x234, 0x18 bytes,
 * up to 4: method 0x10FD00 -> 0x1800A0)") and the neighbour SetShipState__FP2LOi (0x17FD08) show it is the ship's
 * gun list. SafeHouse gives the function no name, so it keeps its address name. */
typedef int OID;
struct HACKGUN {                   /* layout: SafeHouse port (hack.cpp HACKGUN) */
    /* 0x00 */ OID oidPart;        /* field: SafeHouse port - the record (tag oid) the right stick turns */
    /* 0x04 */ OID oidSm;          /* field: SafeHouse port - the state machine run on the ship */
    /* 0x08 */ char pad8[0x18 - 0x08];   /* (resolved at load: xf, control, sm, sma) */
};
struct SHIP {
    /* 0x000 */ char pad0[0x230];
    /* 0x230 */ unsigned int cgun;            /* field: SafeHouse port */
    /* 0x234 */ struct HACKGUN agun[4];       /* field: SafeHouse port */
};

void func_001800A0(struct SHIP *pship, OID oidPart, OID oidSm)
{
    unsigned int i = pship->cgun;
    if (i < 4) {
        struct HACKGUN *pgun;
        pship->cgun = i + 1;
        pgun = &pship->agun[i];
        pgun->oidPart = oidPart;
        pgun->oidSm = oidSm;
    }
}
