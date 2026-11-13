/* FGuardState: whether the guard's state mask (+0x2C0, 64 bits) has state index n (0x2099F0). Layout: SafeHouse port
 * (guard.h GUARD grfState). */
struct GUARD {
    /* 0x000 */ char pad0[0x2c0];
    /* 0x2c0 */ unsigned long grfState;   /* field: SafeHouse port */
};
int func_002099F0(unsigned long grf, int n);   /* the mask has index n */

// name: SafeHouse port (FGuardState, guard.h)
int FGuardState__FP5GUARDi(struct GUARD *pguard, int n)
{
    return func_002099F0(pguard->grfState, n);
}
