/* class: SOEHANDLE (SafeHouse spliceglue.cpp RefSoeOption: option 122's getter, orig 0x256350). */
struct ALO;
struct SOE {
    /* 0x00 */ char pad0[0x14];
    /* 0x14 */ short n14;   /* option 123 */
    /* 0x16 */ short pad16;
    /* 0x18 */ int n18;     /* option 122 */
};
/* a script handle on one of an ALO's entries */
struct SOEHANDLE {
    /* 0x00 */ char pad0[0x20];
    /* 0x20 */ struct ALO *palo;
    /* 0x24 */ struct SOE *psoe;
};

int func_00256350(struct SOEHANDLE *phandle)
{
    return phandle->psoe->n18;
}
