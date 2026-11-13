/* CopyRopeDistances: a rope's rest distances (+0x5C) copied from its path curve's (+0x48: the curve's distance
 * table +0xF0, its count +0xE8). Layout: SafeHouse port (rope.cpp ROPE). */
struct ROPECRV {
    /* 0x00 */ char pad0[0xe8];
    /* 0xe8 */ int cs;
    /* 0xec */ char padec[0xf0 - 0xec];
    /* 0xf0 */ float *as;    /* field: SafeHouse port - the distances */
};
struct ROPE {
    /* 0x00 */ char pad0[0x48];
    /* 0x48 */ struct ROPECRV *pcrv;
    /* 0x4c */ char pad4c[0x5c - 0x4c];
    /* 0x5c */ float *as5C;   /* field: SafeHouse port - the rest distances */
};
void CopyAb(void *pvDst, void *pvSrc, unsigned int cb) asm("CopyAb__FPvT0Ui");

// name: SafeHouse port (CopyRopeDistances)
void CopyRopeDistances__FP4ROPE(struct ROPE *prope)
{
    CopyAb(prope->as5C, prope->pcrv->as, prope->pcrv->cs * sizeof(float));
}
