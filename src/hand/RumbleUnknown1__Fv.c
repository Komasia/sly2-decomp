/* RumbleUnknown1 (SafeHouse port: EnableVibration): the vibration option is 0 at boot (no rumble) and becomes 1
 * (the saved progress record decides) once the title is shown. */
extern int D_002C2D8C;   /* the vibration option (name: SafeHouse port, rumble.h g_vibrationSetting) */

#define VIBRATION_Boot 0
#define VIBRATION_Title 1

void RumbleUnknown1__Fv(void)
{
    if (D_002C2D8C == VIBRATION_Boot)
        D_002C2D8C = VIBRATION_Title;
}
