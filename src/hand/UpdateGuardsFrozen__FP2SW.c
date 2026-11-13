/* UpdateGuardsFrozen (the world update's pass after the update table): the guards' freeze is over after 6 s
 * (D_002BF938). */
struct SW {
    /* 0x0000 */ char pad0[0x4748];
    /* 0x4748 */ int fFrozen;
    /* 0x474c */ float tFrozen;
};
extern float D_002BF938;   /* 6.0 */
extern float g_clock;      /* g_clock.t */
void func_0019F170(struct SW *psw, int fFrozen);   /* SafeHouse: SetGuardsFrozen */

// name: SafeHouse port (UpdateGuardsFrozen)
void UpdateGuardsFrozen__FP2SW(struct SW *psw)
{
    if (psw->fFrozen && D_002BF938 < g_clock - psw->tFrozen)
        func_0019F170(psw, 0);
}
