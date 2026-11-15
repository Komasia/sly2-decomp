/* func_001DE2A0: Init of class 0x54 (CID_ALO_54, the laser's base, derived from SO): the SO init, then the object
 * is made its own tree root (the qword flags at +0x148, bit 34: so.h SO::fTreeRoot). */
#define GRFSO_TreeRoot 0x400000000UL   /* bit 34 of SO +0x148 */

struct SO54 { char unk_so[0x148]; unsigned long grf; };   /* the SO base, up to its flags qword */
void InitSo__FP2SO(struct SO54 *pso);

void func_001DE2A0(struct SO54 *pso)
{
    InitSo__FP2SO(pso);
    pso->grf |= GRFSO_TreeRoot;
}
