/* FK2Done: a kind-2 player is done in its state 4. Layout: SafeHouse port (guard.h K2PLAY). */
struct K2PLAY {
    /* 0x00 */ char pad0[0x10];
    /* 0x10 */ int st;   /* field: SafeHouse port */
};

// name: SafeHouse port (FK2Done, guard.cpp)
int FK2Done__FP6K2PLAY(struct K2PLAY *pk)
{
    return pk->st == 4;
}
