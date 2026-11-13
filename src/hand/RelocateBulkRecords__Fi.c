/* RelocateBulkRecords: the current shader group's bulk records (TEXK 1) relocated into the loaded bulk block at pb:
 * each CLUT's colours (0x20-byte records, D_003DCFF8 / D_003DCFFC) moved and colour-adjusted (AdjustRgba), each
 * BMP's pixels (0x28-byte records, D_003DCFF0 / D_003DCFF4) moved. Layout: SafeHouse port (shd.h CLUT, BMP). */
struct CLUT {
    /* 0x00 */ int id;                 /* field: SafeHouse port */
    /* 0x04 */ unsigned char texk;     /* field: SafeHouse port (1: bulk) */
    /* 0x05 */ char pad5[8 - 5];
    /* 0x08 */ unsigned short ccolor;  /* field: SafeHouse port */
    /* 0x0a */ unsigned short cgsbit;  /* field: SafeHouse port */
    /* 0x0c */ unsigned int *prgba;    /* the colours (before: the offset in the bulk block, ibBulk) */
    /* 0x10 */ char pad10[0x20 - 0x10];
};
struct BMP {
    /* 0x00 */ int id;                 /* field: SafeHouse port */
    /* 0x04 */ unsigned char texk;     /* field: SafeHouse port (1: bulk) */
    /* 0x05 */ char pad5[0x14 - 5];
    /* 0x14 */ int pb;                 /* the pixels (before: the offset in the bulk block, ibBulk) */
    /* 0x18 */ char pad18[0x28 - 0x18];
};
extern int D_003DCFF0;            /* the group's BMPs */
extern struct BMP *D_003DCFF4;
extern int D_003DCFF8;            /* the group's CLUTs */
extern struct CLUT *D_003DCFFC;
void AdjustRgba__FPUi(unsigned int *prgba);

// name: SafeHouse port (RelocateBulkRecords)
void RelocateBulkRecords__Fi(int pb)
{
    int iclut, ibmp;
    for (iclut = 0; iclut < D_003DCFF8; iclut++) {
        struct CLUT *pclut = &D_003DCFFC[iclut];
        if (pclut->texk == 1) {
            unsigned int *prgba;
            pclut->prgba = (unsigned int *)(pb + (int)pclut->prgba);
            for (prgba = pclut->prgba; prgba < pclut->prgba + pclut->ccolor; prgba++)
                AdjustRgba__FPUi(prgba);
        }
    }
    for (ibmp = 0; ibmp < D_003DCFF0; ibmp++) {
        struct BMP *pbmp = &D_003DCFF4[ibmp];
        if (pbmp->texk == 1)
            pbmp->pb = pb + pbmp->pb;
    }
}
