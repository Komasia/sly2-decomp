void func_00205478(void *p, int a, int b);
void PlayActorScriptAnim__FP2LOiii(void *p, int a, int b, int c);
void SetBinocState__FP5ACTORi(void *p, int a);
void func_001442D0(char *p, int a, int b)
{
    func_00205478(p, a, b);
    if (b) {
        if (++*(int *)(p + 0x12F4) == 1) {
            PlayActorScriptAnim__FP2LOiii(p, 0x60B, 9, 5);
            SetBinocState__FP5ACTORi(p + 0xF00, -1);
        }
    }
}
