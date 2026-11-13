/* class: the ropes (SafeHouse rope.cpp: option 1046 / EOPID 1212's getter, the mode - -1 without a simulation). */
struct ROPESIM {
    /* 0x00 */ char pad0[0x4c];
    /* 0x4c */ int mode;
};
struct ROPE {
    /* 0x000 */ char pad0[0x17c];
    /* 0x17c */ struct ROPESIM *psim;
};

int func_001E7FF0(struct ROPE *prope)
{
    struct ROPESIM *psim = prope->psim;
    int mode = -1;
    if (psim != 0) {
        mode = psim->mode;
    }
    return mode;
}
