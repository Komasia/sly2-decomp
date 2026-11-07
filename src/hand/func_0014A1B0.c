void Init__5AIJOB(void *p);
void func_001FEE90(void *p);
void AddGuardState__FP5GUARDi(void *p, int n);
extern char D_003DD040[];
// name: SafeHouse port (JOBCHASE::Init)
void Init__8JOBCHASE(char *p)
{
    Init__5AIJOB(p);
    func_001FEE90(D_003DD040);
    AddGuardState__FP5GUARDi(*(void **)(p + 0x10), 0x24);
    *(int *)(p + 0x30) = -1;
    *(int *)(p + 0x40) = -1;
    *(int *)(p + 0x3C) = -1;
}
