/* CTRLLOOKAT::Query: a look-at controller's goal and its rate are its record's (XF +0xC0 / +0xD0). */
typedef int qword __attribute__((mode(TI)));
struct XF {
    /* 0x00 */ char pad0[0xc0];
    /* 0xc0 */ qword vecGoal;
    /* 0xd0 */ qword dvecGoal;
};
struct CTRLLOOKAT {
    /* 0x00 */ char pad0[8];
    /* 0x08 */ struct XF *pxf;   /* field: SafeHouse port (CTRL) */
};

// name: SafeHouse port (CTRLLOOKAT::Query)
void Query__10CTRLLOOKATP7VECTOR4T1f(struct CTRLLOOKAT *pctrl, qword *pvec, qword *pdvec)
{
    if (pvec)
        *pvec = pctrl->pxf->vecGoal;
    if (pdvec)
        *pdvec = pctrl->pxf->dvecGoal;
}
