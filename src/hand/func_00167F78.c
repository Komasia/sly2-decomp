void func_00167E58(int n);
void iFlushCache(int n);
int func_00167F78(void)
{
    func_00167E58(0x1100C320);
    iFlushCache(0);
    *(volatile int *)0x10003C10 = 8;
    asm volatile("sync\n\tei");
    return -1;
}
