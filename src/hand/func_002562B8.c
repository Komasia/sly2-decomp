/* class: SOEHANDLE (beside options 122 / 123's accessors): the entry's +0x8 setter, the ALO marked dirty. */
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
void MarkAloDirty__FP3ALO(struct ALO *palo);

void func_002562B8(struct SOEHANDLE *phandle, float g)
{
    phandle->psoe->g8 = g;
    MarkAloDirty__FP3ALO(phandle->palo);
}
