void func_001C3ED8(void *p, int n);
void func_001F82B8(void *p, int a, int b);
void func_001EECD0(void *p);
// name: SafeHouse port (SetActorControl)
void SetActorControl__FP2LOi(char *p, int n)
{
    func_001C3ED8(p, n);
    func_001F82B8(p, n == 1 ? 0 : -1, 0);
    if (n == 1) func_001EECD0(p + 0x26C);
}
