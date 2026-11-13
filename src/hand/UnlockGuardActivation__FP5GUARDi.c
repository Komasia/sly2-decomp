/* UnlockGuardActivation: drop one of the job locks that keep a guard active (GUARD +0xFFC); the last one lets the
 * guard deactivate (func_001A6CA8(pguard, 0)). */
struct GUARD {
    /* 0x000 */ char pad0[0xffc];
    /* 0xffc */ int cActivationLocks;   /* field: SafeHouse port */
};
void func_001A6CA8(struct GUARD *pguard, int n);

// name: SafeHouse port (UnlockGuardActivation)
void UnlockGuardActivation__FP5GUARDi(struct GUARD *pguard, int n)
{
    int c = pguard->cActivationLocks - 1;
    pguard->cActivationLocks = c;
    if (c == 0)
        func_001A6CA8(pguard, 0);
}
