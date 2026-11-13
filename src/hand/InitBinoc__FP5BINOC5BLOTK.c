/* InitBinoc: the binocucom (an actor's +0xF00): its kind, no state (-1), and its window part (0x19D4D0).
 * Layout: SafeHouse port (actor.h BINOC). */
struct BINOCWIN {
    /* 0x00 */ int n0;
};
struct BINOC {
    /* 0x00 */ int blotk;                /* the binocucom kind */
    /* 0x04 */ int state;                /* -1 off */
    /* 0x08 */ float tState;             /* field: SafeHouse port */
    /* 0x0c */ char pad0c[0x20 - 0x0c];
    /* 0x20 */ int n20;
    /* 0x24 */ struct BINOCWIN win;      /* field: SafeHouse port */
};
void func_0019D4D0(struct BINOCWIN *pwin, struct BINOC *pbinoc);   /* SafeHouse: the window part's init */

// name: SafeHouse port (InitBinoc)
void InitBinoc__FP5BINOC5BLOTK(struct BINOC *pbinoc, int blotk)
{
    pbinoc->blotk = blotk;
    pbinoc->state = -1;
    pbinoc->n20 = -1;
    func_0019D4D0(&pbinoc->win, pbinoc);
}
