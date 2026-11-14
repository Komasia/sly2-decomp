/* class: an object whose +0x144 is a world record (a vtable entry at 0x2B43D4): 0x2109D0 on that record. */
typedef struct WREC WREC;
typedef struct LO144 {
    /* 0x000 */ char pad0[0x144];
    /* 0x144 */ WREC *pwrec;
} LO144;

int func_002109D0(WREC *pwrec);

void func_00228518(LO144 *plo)
{
    func_002109D0(plo->pwrec);
}
