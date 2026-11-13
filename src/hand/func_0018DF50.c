/* class: JT, Sly (SafeHouse interactsplice.cpp, EOPID 770 / option 753: the hypnosis request +0x1D30). */
struct JT {
    /* 0x0000 */ char pad0[0x1d30];
    /* 0x1d30 */ int fHypnosis;   /* field: SafeHouse port (f1D30) */
};

void func_0018DF50(struct JT *pjt, int f)
{
    pjt->fHypnosis = f;
}
