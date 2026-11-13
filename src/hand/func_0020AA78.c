/* class: GUARD (SafeHouse launcher.cpp, orig 0x0020AA78: the guards' splice method 0x102988 - an action added, then
 * resolved at once (0x20AAA8)). */
struct LO;
void AddGuardAction__FP2LOi(struct LO *plo, int n);
void func_0020AAA8(struct LO *plo);

void func_0020AA78(struct LO *plo, int n)
{
    AddGuardAction__FP2LOi(plo, n);
    func_0020AAA8(plo);
}
