extern float g_clock;
void func_0014F750(char *p, int a)
{
    *(float *)(p + 0x618) = g_clock;
    *(int *)(p + 0x61C) = a;
}
