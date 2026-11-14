/* class: GUARD (SafeHouse guardstart.cpp: 0x102B60 -> 0x207BC8, a kind entry set by the live splice method and the
 * replaced entry resolved at once). */
struct GUARD;
struct KINDE;
unsigned long MaskOfList__FPv(void *plist);
struct KINDE *PkindeOfMask__FP5GUARDUl(struct GUARD *pguard, unsigned long mask);
void SetGuardKinde__FP5GUARD3OIDii(struct GUARD *pguard, void *plist, int n1, int n2);
void ResolveKinde__FP5KINDEP5GUARD(struct KINDE *pkinde, struct GUARD *pguard);

void func_00207BC8(struct GUARD *pguard, void *plist, int n1, int n2)
{
    struct KINDE *pkinde = PkindeOfMask__FP5GUARDUl(pguard, MaskOfList__FPv(plist));
    SetGuardKinde__FP5GUARD3OIDii(pguard, plist, n1, n2);
    ResolveKinde__FP5KINDEP5GUARD(pkinde, pguard);
}
