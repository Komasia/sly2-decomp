/* func_0020D460 (0x20D460): the water watcher's (+0x49C) water (+0xC), set by the
 * guard's messages 4 / 5. */
struct LO;
struct WATCHB {
    /* 0x0 */ char pad0[0xc];
    /* 0xc */ struct LO *plo;   /* field: SafeHouse port */
};

void func_0020D460(struct WATCHB *pwatch, struct LO *plo)
{
    pwatch->plo = plo;
}
