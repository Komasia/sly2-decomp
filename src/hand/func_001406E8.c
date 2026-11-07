void EnablePo__FP2POi(void *p, int n);
void func_001F82B8(void *p, int a, int b);
void ClearJobs__FP5ACTOR(void *p);
// name: SafeHouse port (SetActorControl)
void SetActorControl__FP2LOi(char *p, int n)
{
    EnablePo__FP2POi(p, n);
    func_001F82B8(p, n == 1 ? 0 : -1, 0);
    if (n == 1) ClearJobs__FP5ACTOR(p + 0x26C);
}
