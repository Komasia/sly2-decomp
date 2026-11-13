/* class: CTRLCHAIN, the chain's controller of a segment's record (kind 3, SafeHouse chain.cpp, orig 0x21C858 Start):
 * the base start, then the segment +0x1C back in the record's +0xA8. */
struct ALOCHAINE;
struct XFREC {
    /* 0x00 */ char pad0[0xa8];
    /* 0xa8 */ struct ALOCHAINE *pe;
};
struct CTRLCHAIN {
    /* 0x00 */ char pad0[8];
    /* 0x08 */ struct XFREC *pxf;
    /* 0x0c */ char padc[0x1c - 0xc];
    /* 0x1c */ struct ALOCHAINE *pe;   /* field: SafeHouse port */
};
void Start__4CTRL(struct CTRLCHAIN *pctrl);

void func_0021C858(struct CTRLCHAIN *pctrl)
{
    Start__4CTRL(pctrl);
    pctrl->pxf->pe = pctrl->pe;
}
