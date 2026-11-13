/* class: BENTLEY (vt slot 105, the ability display; the actors' base 0x141E70 does nothing). SafeHouse gadget.cpp:
 * Bentley shows his Hover Pack (glob group 0x24D) while he is the current player and ability 12 (Hover Pack) is on
 * one of his buttons, else hides it. */
struct BENTLEY;
void func_00141E70(struct BENTLEY *pbentley);                 /* the base slot 105 */
int func_001C40C0(struct BENTLEY *pbentley);                  /* the current player? */
int func_00141EA8(struct BENTLEY *pbentley, int idAbility);   /* the buttons the ability is on */
void ShowAloGlobs__FP3ALOi(struct BENTLEY *palo, int idGroup);
void func_001F69F8(struct BENTLEY *palo, int idGroup);        /* hides the glob group */

void func_00136C50(struct BENTLEY *pbentley)
{
    func_00141E70(pbentley);
    if (func_001C40C0(pbentley) != 0 && func_00141EA8(pbentley, 12) != 0) {
        ShowAloGlobs__FP3ALOi(pbentley, 0x24D);
        return;
    }
    func_001F69F8(pbentley, 0x24D);
}
