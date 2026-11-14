extern struct G { char pad[0x4764]; int a; int b; } g_sw;
extern char D_002A8AA8[];
void sprintf(void *f, const char *fmt, ...);
void func_00210F50(void *f)
{
    sprintf(f, D_002A8AA8, g_sw.a, g_sw.b);
}
