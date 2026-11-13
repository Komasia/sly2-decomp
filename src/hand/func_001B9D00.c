/* class: MURRAY (SafeHouse gang.cpp: method 941 -> 0x1B9D00, the Thunder Flop entrance: the alternate clip flag
 * +0x13E8 off, state 3). */
struct MURRAY {
    /* 0x0000 */ char pad0[0x13e8];
    /* 0x13e8 */ int fFlopAlt;   /* field: SafeHouse port (f13E8) - use the alternate Thunder Flop clip */
};
void func_001B6078(struct MURRAY *pmurray, int state, int n);   /* SafeHouse: SetMurrayState */

void func_001B9D00(struct MURRAY *pmurray, int n1, int n2)
{
    pmurray->fFlopAlt = 0;
    func_001B6078(pmurray, 3, n2);
}
