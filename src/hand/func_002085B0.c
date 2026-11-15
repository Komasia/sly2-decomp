/* func_002085B0 (0x2085B0): a script's "add target" (EOPID 261): the object added to the guard's detector entries
 * (0x2085D0, not in front). */
struct GUARD;
struct LO;
void func_002085D0(struct GUARD *pguard, struct LO *plo, int fFront);

void func_002085B0(struct GUARD *pguard, struct LO *plo, int n)
{
    func_002085D0(pguard, plo, 0);
}
