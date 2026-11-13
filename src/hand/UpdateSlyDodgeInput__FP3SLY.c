/* UpdateSlyDodgeInput: while dodging, Sly keeps facing the object he faces (ACTOR +0x10DC). The argument is his
 * dodge record, whose first word is the actor. */
struct LO;
struct ACTOR {
    /* 0x0000 */ char pad0[0x10dc];
    /* 0x10dc */ struct LO *ploFace;   /* field: SafeHouse port (plo10DC, "the object faced") */
};
struct SLYDODGE {
    /* 0x0 */ struct ACTOR *pactor;
};
void FaceObject(struct ACTOR *pactor, struct LO *plo) asm("FaceObject__FP5ACTORP2LO");

// name: SafeHouse port (UpdateSlyDodgeInput)
void UpdateSlyDodgeInput__FP3SLY(struct SLYDODGE *pdodge)
{
    struct ACTOR *pactor = pdodge->pactor;
    struct LO *plo = pactor->ploFace;
    if (plo)
        FaceObject(pactor, plo);
}
