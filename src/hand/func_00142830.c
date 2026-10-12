void func_001427C8(void *p, int a, int b);
void func_00142830(char *p, int a, int b)
{
    func_001427C8(p, a, b);
    *(int *)(p + 0x1100) = 1;
}
