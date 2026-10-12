int DIntr(void)
{
    int eie, res, st;
    __asm__ volatile("mfc0 %0, $12" : "=r"(eie));
    eie &= 0x10000;
    if (eie) {
        res = eie != 0;
        __asm__(".p2align 3");
    loop:
        __asm__ volatile("di");
        __asm__ volatile("sync.p");
        __asm__ volatile("mfc0 %0, $12" : "=r"(st));
        st &= 0x10000;
        __asm__ volatile("nop\n\tnop");
        if (st) goto loop;
        __asm__ volatile("");
    } else
        res = 0;
    return res;
}

