struct WRE { char pad[0x64]; float x; };
struct WRE *func_0022C4D8(void *p, int a);
float func_0022C570(void *p)
{
    struct WRE *pwre = func_0022C4D8(p, 1);
    if (pwre->x == 0.0f) return 0.0f;
    return 1.0f / pwre->x;
}
