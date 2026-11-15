/* A hold on the actor released (the base 0x205588): the last one (+0x12F4) ends the script animation. */
void func_00205588(void *pactor, int a, int b);
void EndActorScriptAnim__FP5ACTOR(void *pactor);
void func_00144338(char *pactor, int a, int b)
{
    func_00205588(pactor, a, b);
    if (b) {
        if (--*(int *)(pactor + 0x12F4) == 0) EndActorScriptAnim__FP5ACTOR(pactor);
    }
}
