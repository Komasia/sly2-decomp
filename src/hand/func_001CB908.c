/* class: CID_0D, the rail (a PATH kind, vt slot 7 = InitLo; SafeHouse interact.cpp: +0x1C0 1000 / +0x1C4 1 unless
 * the options set them): the path's init, then +0x190's record and those two. */
struct RAIL {
    /* 0x000 */ char pad0[0x190];
    /* 0x190 */ char sub190[0x30];   /* initialised by 0x182C70 */
    /* 0x1c0 */ float g1C0;
    /* 0x1c4 */ float g1C4;
};
void func_001E5D80(struct RAIL *ppath);   /* the base InitLo (PATH) */
void func_00182C70(void *p);

void func_001CB908(struct RAIL *prail)
{
    func_001E5D80(prail);
    func_00182C70(prail->sub190);
    prail->g1C4 = 1.0f;
    prail->g1C0 = 1000.0f;
}
