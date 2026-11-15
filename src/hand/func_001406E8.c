/* SetActorControl: the actor's control (PO enable n); under the player's control (1) its +0x1F82B8 field cleared and
 * its AI jobs (+0x26C) dropped, else set to -1. */
void EnablePo__FP2POi(void *pactor, int n);
void func_001F82B8(void *pactor, int a, int b);
void ClearJobs__FP5ACTOR(void *pactor);
// name: SafeHouse port (SetActorControl)
void SetActorControl__FP2LOi(char *pactor, int n)
{
    EnablePo__FP2POi(pactor, n);
    func_001F82B8(pactor, n == 1 ? 0 : -1, 0);
    if (n == 1) ClearJobs__FP5ACTOR(pactor + 0x26C);
}
