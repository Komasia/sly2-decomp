/* FVisible: a screen render target is visible when its +0x7C is set (!= -1) and no listed target of the same world
 * with a higher priority hides it (0x2137F0). Field: SafeHouse port (screenrt.cpp). */
struct SCREENRT {
    /* 0x00 */ char pad0[0x7c];
    /* 0x7c */ int id7C;      /* field: SafeHouse port (-1: none) */
};
int func_002137F0(struct SCREENRT *prt);

// name: SafeHouse port (FVisible)
int FVisible__FP8SCREENRT(struct SCREENRT *prt)
{
    if (prt->id7C == -1)
        return 0;
    return func_002137F0(prt) == 0;
}
