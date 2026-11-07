struct BIG { int a[0x5408 / 4]; };
extern struct BIG *D_002DEB4C;
extern struct BIG D_003D4A60;
void ApplyVibrationSetting__Fv(void);
void ApplyGameSettings__FP8GAMESAVE(struct BIG *p);
void func_00166008(void)
{
    if (D_002DEB4C) {
        D_003D4A60 = *D_002DEB4C;
        D_002DEB4C = 0;
        ApplyVibrationSetting__Fv();
        ApplyGameSettings__FP8GAMESAVE(&D_003D4A60);
    }
}
