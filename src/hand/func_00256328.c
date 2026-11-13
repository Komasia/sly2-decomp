/* class: SOEHANDLE (SafeHouse spliceglue.cpp RefSoeOption: option 122's setter, orig 0x256328), the ALO marked dirty. */
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

void func_00256328(struct SOEHANDLE *phandle, int n)
{
    phandle->psoe->n18 = n;
    MarkAloDirty__FP3ALO(phandle->palo);
}
