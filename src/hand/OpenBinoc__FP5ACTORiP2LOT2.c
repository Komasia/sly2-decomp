/* OpenBinoc: the binocucom (ACTOR +0xF00) opened in view n (0 recon, 1 a talk with a speaker and a window screen
 * object); a talk while it is on in another view closes it first; while on in a view otherwise nothing happens.
 * Layout: SafeHouse port (actor.h BINOC). */
struct LO;
struct BINOC {
    /* 0x00 */ struct ACTOR *pactor;
    /* 0x04 */ int state;             /* SafeHouse: ACTOR::nF04 (-1 off) */
    /* 0x08 */ char pad8[0x20 - 0x8];
    /* 0x20 */ int nView;
    /* 0x24 */ char pad24[0x40 - 0x24];
    /* 0x40 */ struct LO *ploSpeaker; /* field: SafeHouse port */
    /* 0x44 */ struct LO *ploScreen;  /* field: SafeHouse port */
};
void SetBinocState__FP5ACTORi(struct BINOC *pbinoc, int st);

// name: SafeHouse port (OpenBinoc)
void OpenBinoc__FP5ACTORiP2LOT2(struct BINOC *pbinoc, int nView, struct LO *ploSpeaker, struct LO *ploScreen)
{
    if (pbinoc->state != -1) {
        if (pbinoc->nView == 1 || nView != 1)
            return;
        SetBinocState__FP5ACTORi(pbinoc, 2);
        SetBinocState__FP5ACTORi(pbinoc, -1);
    }
    pbinoc->nView = nView;
    pbinoc->ploSpeaker = ploSpeaker;
    pbinoc->ploScreen = ploScreen;
    SetBinocState__FP5ACTORi(pbinoc, 0);
}
