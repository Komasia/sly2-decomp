/* class: CID_5F, a pickup kind (vt slot 7 = InitLo; SafeHouse pickup.cpp): the pickup's init, then +0x1DC 50. */
struct PICKUP5F {
    /* 0x000 */ char pad0[0x1dc];
    /* 0x1dc */ float g1DC;
};
void InitPickup__FP2LO(struct PICKUP5F *plo);

void func_001C7E38(struct PICKUP5F *ppickup)
{
    InitPickup__FP2LO(ppickup);
    ppickup->g1DC = 50.0f;
}
