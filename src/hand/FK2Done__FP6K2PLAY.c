/* FK2Done (0x20C0D8): whether a kind-2 player is done (K2ST_Done). Layout: SafeHouse port (guard.h K2PLAY). */
#include "h6_guard.h"
struct K2PLAY {
    /* 0x00 */ char pad0[0x10];
    /* 0x10 */ int st;   /* field: SafeHouse port */
};

// name: SafeHouse port (FK2Done, guard.cpp)
int FK2Done__FP6K2PLAY(struct K2PLAY *pk)
{
    return pk->st == K2ST_Done;
}
