/* FAnimatedOverlayDrawNormal: whether the ordinary world and HUD are drawn under the overlay owning the screen: not
 * while it shows its frame (2) or waits for its dialog (3). Layout: SafeHouse port (overlay.cpp). */
struct OVERLAY {
    /* 0x000 */ char pad[0x150];
    /* 0x150 */ int state;   /* field: SafeHouse port */
};
// name: SafeHouse port (FAnimatedOverlayDrawNormal)
int FAnimatedOverlayDrawNormal__FPc(struct OVERLAY *poverlay)
{
    switch (poverlay->state) {
    case 2:
    case 3:
        return 0;
    }
    return 1;
}
