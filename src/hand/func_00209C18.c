/* PkindeOfMask (0x209C18): the guard's kind table entry for the state mask grfKind (appended when new), cleared
 * (0x2090D0). */
struct KINDEM { char pad[0x10]; long grfKind; char pad2[8]; };   /* a KINDE, then its state mask */
struct GUARD { char pad[0x4C0]; int ckindem; char pad2[0xC]; struct KINDEM akindem[1]; };
struct KINDEM *func_00209BE0(struct GUARD *pguard, long grfKind);
void func_002090D0(struct KINDEM *pkindem, struct GUARD *pguard);   /* clears the entry */
// name: SafeHouse port (PkindeOfMask)
struct KINDEM *PkindeOfMask__FP5GUARDUl(struct GUARD *pguard, long grfKind)
{
    struct KINDEM *pkindem = func_00209BE0(pguard, grfKind);
    if (!pkindem) {
        struct KINDEM *pkindemNew = &pguard->akindem[pguard->ckindem++];
        pkindemNew->grfKind = grfKind;
        pkindem = pkindemNew;
    }
    func_002090D0(pkindem, pguard);
    return pkindem;
}
