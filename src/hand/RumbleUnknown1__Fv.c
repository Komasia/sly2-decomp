/* RumbleUnknown1 (SafeHouse port: EnableVibration): the vibration option is 0 at boot (no rumble) and becomes 1
 * once the title is shown. */
extern int D_002C2D8C;   /* the vibration option (name: SafeHouse port, rumble.h) */

void RumbleUnknown1__Fv(void)
{
    if (D_002C2D8C == 0)
        D_002C2D8C = 1;
}
