/* ResetHideInstance: the base reset (func_001CB518), then the hiding spot is free (state 0). */
struct LO {
    /* 0x000 */ char pad0[0x17c];
    /* 0x17c */ int state;   /* field: SafeHouse port (hide.h: 0 free, 1 a player jumping in, 2 a player inside, ...) */
};
void func_001CB518(struct LO *plo);

// name: SafeHouse port (ResetHideInstance)
void ResetHideInstance__FP2LO(struct LO *plo)
{
    func_001CB518(plo);
    plo->state = 0;
}
