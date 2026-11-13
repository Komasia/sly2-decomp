/* class: CID_46, the safe house (vt slot 79 = EnablePo; SafeHouse po.cpp): the PO's enable, then the safe house's
 * state with it (0 or 1). */
struct PO;
void EnablePo__FP2POi(struct PO *ppo, int n);
void SetSafeHouseState__FP2SWi(struct PO *ppo, int state);

void func_001D7418(struct PO *ppo, int n)
{
    EnablePo__FP2POi(ppo, n);
    switch (n) {
    case 0:
        SetSafeHouseState__FP2SWi(ppo, 0);
        return;
    case 1:
        SetSafeHouseState__FP2SWi(ppo, 1);
        break;
    }
}
