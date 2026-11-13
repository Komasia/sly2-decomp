/* class: CID_4D, the vehicles (SafeHouse vehicle.cpp, orig 0x1D1410 / 0x1D4DE0: each clone gets independent BASIC
 * attachments): the 0x9C bytes from +0x14 copied. */
struct VEHICLEPART {
    /* 0x00 */ char pad0[0x14];
    /* 0x14 */ char ab[0x9c];
};
void CopyAb__FPvT0Ui(void *pvDst, void *pvSrc, unsigned int cb);

void func_001D4DE0(struct VEHICLEPART *pdst, struct VEHICLEPART *psrc)
{
    CopyAb__FPvT0Ui(pdst->ab, psrc->ab, 0x9C);
}
