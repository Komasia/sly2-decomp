extern char g_sw[];
extern char D_003DD040[];
void SetSoundMasterVolume__FP8SOUNDMGRf(void *p, float f);
void func_0022B490(void *a, void *b, int c, int d, void *e, int f);
void func_0014C140(void *p)
{
    SetSoundMasterVolume__FP8SOUNDMGRf(D_003DD040, 0.0f);
    func_0022B490(g_sw, 0, 0x189, -1, p, -1);
}
