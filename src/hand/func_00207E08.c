/* func_00207E08 (0x207E08): the live splice method 245 (0x102F38): 0x207D98, then the entry resolved at once. */
long MaskOfList__FPv(int plist);
void *PkindeOfMask__FP5GUARDUl(void *pguard, long grf);
void func_00207D98(void *pguard, int plist, int oid, float a, float b, float c, float d);
void ResolveKinde__FP5KINDEP5GUARD(void *pkinde, void *pguard);
void func_00207E08(void *pguard, int plist, int oid, float a, float b, float c, float d)
{
    void *pkinde = PkindeOfMask__FP5GUARDUl(pguard, MaskOfList__FPv(plist));
    func_00207D98(pguard, plist, oid, a, b, c, d);
    ResolveKinde__FP5KINDEP5GUARD(pkinde, pguard);
}
