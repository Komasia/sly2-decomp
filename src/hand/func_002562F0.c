/* class: SOEHANDLE (SafeHouse spliceglue.cpp RefSoeOption: option 123's setter, orig 0x2562F0), the ALO marked dirty. */
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
void MarkAloDirty__FP3ALO(struct ALO *palo);

void func_002562F0(struct SOEHANDLE *phandle, short n)
{
    phandle->psoe->n14 = n;
    MarkAloDirty__FP3ALO(phandle->palo);
}
