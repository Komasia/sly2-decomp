/* FK3Done: a kind-3 player is done when it plays no animation (+0x24). Layout: SafeHouse port (kind3.cpp K3PLAY). */
struct ASEGA;
struct K3PLAY {
    /* 0x00 */ char pad0[0x24];
    /* 0x24 */ struct ASEGA *pasega;   /* field: SafeHouse port */
};

// name: SafeHouse port (FK3Done, kind3.cpp)
int FK3Done__FP6K3PLAY(struct K3PLAY *pk)
{
    return pk->pasega == 0;
}
