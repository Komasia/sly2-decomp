/* class: ACTOR (SafeHouse scpt.cpp: a script waits on it until the throw controller is back in state -1). */
struct ACTOR {
    /* 0x0000 */ char pad0[0x11b4];
    /* 0x11b4 */ int stThrow;   /* field: SafeHouse port - jtthrow.state */
};

int func_001424C0(struct ACTOR *pactor)
{
    return pactor->stThrow == -1;
}
