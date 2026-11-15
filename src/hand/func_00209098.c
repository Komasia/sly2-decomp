/* func_00209098 (0x209098): whether the guard is held still: its fStill flag (+0xFC8), or the game paused for the
 * guards (0x20F1B8). Field: SafeHouse port (guard.h FGuardStill). */
struct SW;
extern struct SW g_sw;
struct GUARD { char pad[0xFC8]; int fStill; };
int func_0020F1B8(struct SW *psw);   /* the guards' pause */
int func_00209098(struct GUARD *pguard) { if (pguard->fStill != 0) return 1; return func_0020F1B8(&g_sw); }
