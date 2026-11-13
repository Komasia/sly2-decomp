/* The loaded world's records (SafeHouse transition.h / sw.h: orig 0x3E1C40.., 0x210B98 an episode's main world
 * record): record i (0x40 bytes) when its +0x4 differs from its +0x3C, else null; -1 none. */
struct WREC {
    /* 0x00 */ int n0;
    /* 0x04 */ int n4;
    /* 0x08 */ char pad8[0x3c - 8];
    /* 0x3c */ int n3C;
};
extern struct WREC *D_003E1C50;   /* the records */

struct WREC *func_00210B98(int i)
{
    struct WREC *pwrec;
    int f;
    if (i == -1) {
        return 0;
    }
    pwrec = &D_003E1C50[i];
    f = 0;
    if (pwrec != 0) {
        f = pwrec->n4 != pwrec->n3C;
    }
    return f == 0 ? 0 : pwrec;
}
