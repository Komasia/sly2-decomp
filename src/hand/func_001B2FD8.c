int func_001B2FD8(void *p, unsigned int cb, unsigned int pv)
{
    int n = cb & 0xFFFFFFF0;
    if (n > 0x1000) n = 0x1000;
    *(volatile unsigned int *)0x1000B420 = (unsigned int)n >> 4;
    *(volatile unsigned int *)0x1000B410 = pv & 0x0FFFFFFF;
    *(volatile unsigned int *)0x1000B400 = 0x101;
    __asm__ __volatile__("sync");
    return n;
}
