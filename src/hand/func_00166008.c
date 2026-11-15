/* func_00166008: after the load, the pending save (D_002DEB4C) becomes the current game (D_003D4A60) and its settings
 * apply. */
struct GAMESAVE { int a[0x5408 / 4]; };
extern struct GAMESAVE *D_002DEB4C;
extern struct GAMESAVE D_003D4A60;
void ApplyVibrationSetting__Fv(void);
void ApplyGameSettings__FP8GAMESAVE(struct GAMESAVE *pgamesave);
void func_00166008(void)
{
    if (D_002DEB4C) {
        D_003D4A60 = *D_002DEB4C;
        D_002DEB4C = 0;
        ApplyVibrationSetting__Fv();
        ApplyGameSettings__FP8GAMESAVE(&D_003D4A60);
    }
}
