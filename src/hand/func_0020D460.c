/* class: WATCHB, a guard's +0x49C watcher (SafeHouse guard.h / guard.cpp: its object +0xC, the water set by the
 * guard's messages 4 / 5). */
struct LO;
struct WATCHB {
    /* 0x0 */ char pad0[0xc];
    /* 0xc */ struct LO *plo;   /* field: SafeHouse port */
};

void func_0020D460(struct WATCHB *pwatch, struct LO *plo)
{
    pwatch->plo = plo;
}
