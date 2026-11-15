/* func_0020E040 (0x20E040): whether a world change is under way: one is pending (g_sw +0x3BF0) or the wipe is going
 * out (0x443740 state 1). */
extern int D_003E1080;   /* g_sw +0x3BF0: a world change is pending */
extern int D_00443740;   /* the wipe's state (1: out) */
int func_0020E040(void) { if (D_003E1080 != 0) return 1; return D_00443740 == 1; }
