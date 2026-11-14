/* class: an XF handle (SafeHouse xfhandle.cpp: the resolver 0x1F88D8 - the record +0x24, re-armed on a write (1)). */
struct ALO;
struct XF;
struct XFHANDLE {
    /* 0x00 */ char pad0[0x20];
    /* 0x20 */ struct ALO *palo;
    /* 0x24 */ struct XF *pxf;
};
void HoldXfMode(struct ALO *palo, struct XF *pxf);

struct XF *func_001F88D8(struct XFHANDLE *phandle, int fWrite)
{
    if (fWrite == 1) {
        HoldXfMode(phandle->palo, phandle->pxf);
    }
    return phandle->pxf;
}
