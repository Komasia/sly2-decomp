/* class: GUARD (SafeHouse guardstart.cpp, orig 0x2080F0: the kind entries resolved - the table (+0x4C0 of them,
 * 0x20 bytes each from +0x4D0), then +0xC10, +0x8D0, +0xA70). */
struct KINDE {
    /* 0x00 */ char ab[0x20];
};
struct GUARD {
    /* 0x000 */ char pad0[0x4c0];
    /* 0x4c0 */ int ckinde;
    /* 0x4c4 */ char pad4c4[0x4d0 - 0x4c4];
    /* 0x4d0 */ struct KINDE akinde[1];
};
void ResolveKinde__FP5KINDEP5GUARD(struct KINDE *pkinde, struct GUARD *pguard);
void func_002080A0(struct GUARD *pguard, void *p);

void func_002080F0(struct GUARD *pguard)
{
    int i = 0;
    if (pguard->ckinde > 0) {
        struct KINDE *pkinde = pguard->akinde;
        do {
            ResolveKinde__FP5KINDEP5GUARD(pkinde, pguard);
            i++;
            pkinde++;
        } while (i < pguard->ckinde);
    }
    func_002080A0(pguard, (char *)pguard + 0xC10);
    func_002080A0(pguard, (char *)pguard + 0x8D0);
    func_002080A0(pguard, (char *)pguard + 0xA70);
}
