/* class: the dances (SafeHouse dance.cpp: optid 0x10F918 -> 0x153810, a crowd entry - its object, its first state;
 * 0x80 at most). */
struct CROWDENTRY {
    /* 0x00 */ int oid;
    /* 0x04 */ int state;
    /* 0x08 */ int pad8;
    /* 0x0c */ int nC;
    /* 0x10 */ int pad10[3];
};
struct DANCE {
    /* 0x000 */ char pad0[0x2a8];
    /* 0x2a8 */ unsigned int centry;
    /* 0x2ac */ struct CROWDENTRY aentry[0x80];
};

void func_00153810(struct DANCE *pdance, int oid, int state)
{
    unsigned int i = pdance->centry;
    if (i < 0x80) {
        struct CROWDENTRY *pe;
        pdance->centry = i + 1;
        pe = &pdance->aentry[i];
        pe->oid = oid;
        pe->state = state;
        pe->nC = -1;
    }
}
