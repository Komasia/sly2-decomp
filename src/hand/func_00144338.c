void func_00205588(void *p, int a, int b);
void EndActorScriptAnim__FP5ACTOR(void *p);
void func_00144338(char *p, int a, int b)
{
    func_00205588(p, a, b);
    if (b) {
        if (--*(int *)(p + 0x12F4) == 0) EndActorScriptAnim__FP5ACTOR(p);
    }
}
