/* NCmpWkr (Sly 1 jt.c name): orders two WKRs by the float at their start (Sly 2 layout; ascending, ties count as
 * smaller), as a sort comparator. */
struct WKR { float g; /* +0x0; the rest of the Sly 2 WKR is not used here */ };

int NCmpWkr(WKR *pwkr0, WKR *pwkr1)
{
    int n = -1;

    if (pwkr0->g > pwkr1->g) {
        n = 1;
    }
    return n;
}
