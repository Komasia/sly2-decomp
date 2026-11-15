/* A hold on the actor (the base 0x205478): the first one (+0x12F4 counts them) plays the script animation 0x60B
 * (flags 9, 5) and closes the binoculars. */
void func_00205478(void *pactor, int a, int b);
void PlayActorScriptAnim__FP2LOiii(void *pactor, int a, int b, int c);
void SetBinocState__FP5ACTORi(void *pactor, int a);
void func_001442D0(char *pactor, int a, int b)
{
    func_00205478(pactor, a, b);
    if (b) {
        if (++*(int *)(pactor + 0x12F4) == 1) {
            PlayActorScriptAnim__FP2LOiii(pactor, 0x60B, 9, 5);
            SetBinocState__FP5ACTORi(pactor + 0xF00, -1);
        }
    }
}
