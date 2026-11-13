/* class: BUTTON, the touch pads (cid 0x53; SafeHouse pad.cpp: module 0x148B18..0x1492F0): 0x148620 on its +0x48. */
struct BUTTON {
    /* 0x00 */ char pad0[0x48];
    /* 0x48 */ char sub48[4];
};
void func_00148620(void *p);

void func_00148B18(struct BUTTON *pbutton)
{
    func_00148620(pbutton->sub48);
}
