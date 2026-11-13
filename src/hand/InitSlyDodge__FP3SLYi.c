/* InitSlyDodge: set up Sly's dodge record (SLY +0x1FF0): its owner value n, no dodge state (-1). */
struct SLYDODGE {
    /* 0x0 */ int n;
    /* 0x4 */ int state;   /* field: SafeHouse port (dodge.state = -1) */
};

// name: SafeHouse port (InitSlyDodge)
void InitSlyDodge__FP3SLYi(struct SLYDODGE *pdodge, int n)
{
    pdodge->n = n;
    pdodge->state = -1;
}
