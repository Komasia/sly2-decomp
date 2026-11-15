/* func_00167F78: the VU1 interrupt handler (installed by StartupFrame on INTC 5): convert the VU1 output at
 * 0x1100C320 (func_00167E58), flush the cache, acknowledge the interrupt and re-enable interrupts. */
void func_00167E58(int pvVu1Mem);
void iFlushCache(int n);
int func_00167F78(void)
{
    func_00167E58(0x1100C320);
    iFlushCache(0);
    *(volatile int *)0x10003C10 = 8;
    asm volatile("sync\n\tei");
    return -1;
}
