/* LoadBtn: a button component remembers the object that owns it (BTN +0x0). In Sly 2 that is all it does.
 * name: Sly 1 LoadBtn__FP3BTNP3ALO (called by LoadButtonFromBrx / LoadVolbtnFromBrx with (&pbutton->btn, pbutton),
 * where Sly 1 calls LoadBtn). */
struct ALO;
struct BTN {
    /* 0x00 */ struct ALO *paloOwner;
};

void LoadBtn__FP3BTNP3ALO(struct BTN *pbtn, struct ALO *paloOwner)
{
    pbtn->paloOwner = paloOwner;
}
