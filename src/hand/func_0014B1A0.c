void func_00205EB8(void *p);
extern void *D_002DD648;
void func_0014B1A0(char *p)
{
    func_00205EB8(p);
    D_002DD648 = p;
    *(int *)(p + 0x4A4) = 1;
}
