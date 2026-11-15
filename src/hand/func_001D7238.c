/* class: the safe house, class 0x46 (vt slot 7, its InitLo): the PO init, then remember it in D_003D4A54
 * (D_003D4A54). */
void InitPo__FP2PO(void *ppo);
extern void *D_003D4A54;      /* the safe house (read by func_00140ED8) */

void func_001D7238(void *psh)
{
    InitPo__FP2PO(psh);
    D_003D4A54 = psh;
}
