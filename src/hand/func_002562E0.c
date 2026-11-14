/* class: SOEHANDLE (beside options 122 / 123's accessors, 0x2562F0..): the entry's +0x8 getter. */
struct ALO;
struct SOE {
    /* 0x0 */ char pad0[8];
    /* 0x8 */ float g8;
};
/* a script handle on one of an ALO's entries (SafeHouse spliceglue.cpp RefSoeOption) */
struct SOEHANDLE {
    /* 0x00 */ char pad0[0x20];
    /* 0x20 */ struct ALO *palo;
    /* 0x24 */ struct SOE *psoe;
};

float func_002562E0(struct SOEHANDLE *phandle)
{
    return phandle->psoe->g8;
}
