/* func_00207CF8 (0x207CF8): the live splice method 244 (0x102D30): SetGuardKind3, then the entry resolved at once. */
long MaskOfList__FPv(int plist);
void *PkindeOfMask__FP5GUARDUl(void *pguard, long grf);
void SetGuardKind3__FP5GUARDiiiii(void *pguard, int plist, int oid0, int oid1, int oid2, int oid3);
void ResolveKinde__FP5KINDEP5GUARD(void *pkinde, void *pguard);
void func_00207CF8(void *pguard, int plist, int oid0, int oid1, int oid2, int oid3)
{
    void *pkinde = PkindeOfMask__FP5GUARDUl(pguard, MaskOfList__FPv(plist));
    SetGuardKind3__FP5GUARDiiiii(pguard, plist, oid0, oid1, oid2, oid3);
    ResolveKinde__FP5KINDEP5GUARD(pkinde, pguard);
}
