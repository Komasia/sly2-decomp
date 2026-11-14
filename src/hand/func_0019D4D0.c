/* The binocucom's window part (SafeHouse binoc.h: the actor's +0xF24, 0x19D4D0..): its owner, no state, and for Sly
 * (cid 0x35) his +0x1D40 part started (0x201D78). */
struct ACTOR;
struct BINOCWND {
    /* 0x00 */ struct ACTOR **ppactor;
    /* 0x04 */ int state;
    /* 0x08 */ char pad8[0x14 - 8];
    /* 0x14 */ void *ppart;
};
int FIsBasicDerivedFrom__FP5BASIC3CID(struct ACTOR *pbasic, int cid);
void func_00201D78(void *ppart, struct ACTOR **ppactor);

void func_0019D4D0(struct BINOCWND *pwnd, struct ACTOR **ppactor)
{
    pwnd->ppactor = ppactor;
    pwnd->state = -1;
    if (FIsBasicDerivedFrom__FP5BASIC3CID(*ppactor, 0x35) != 0) {
        void *ppart = (char *)*pwnd->ppactor + 0x1D40;
        pwnd->ppart = ppart;
        func_00201D78(ppart, ppactor);
        return;
    }
    pwnd->ppart = 0;
}
