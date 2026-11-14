/* class: CID_67, the booty (SafeHouse booty.cpp: EOPID 1152 -> 0x13C3B8, a record {id, n4, n14} added (32 at most,
 * 0x2C bytes each from +0x154) and made current). */
struct BOOTYREC {
    /* 0x00 */ int id;
    /* 0x04 */ int n4;
    /* 0x08 */ int pad8[3];
    /* 0x14 */ int n14;
    /* 0x18 */ int n18;
    /* 0x1c */ int n1C;
    /* 0x20 */ int pad20[3];
};
struct BOOTY {
    /* 0x000 */ char pad0[0x150];
    /* 0x150 */ int crec;
    /* 0x154 */ struct BOOTYREC *arec;
    /* 0x158 */ struct BOOTYREC *precCur;   /* the current record */
};
void func_0013C440(struct BOOTY *pbooty);   /* no current record */

void func_0013C3B8(struct BOOTY *pbooty, int id, int n4, int n14)
{
    int i;
    func_0013C440(pbooty);
    i = pbooty->crec;
    if (i < 0x20) {
        struct BOOTYREC *prec;
        pbooty->crec = i + 1;
        prec = &pbooty->arec[i];
        pbooty->precCur = prec;
        prec->id = id;
        prec->n4 = n4;
        prec->n14 = n14;
        prec->n18 = -1;
        prec->n1C = 0;
    }
}
