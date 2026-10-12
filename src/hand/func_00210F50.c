extern struct G { char pad[0x4764]; int a; int b; } D_003DD490;
extern char D_002A8AA8[];
void fiprintf(void *f, const char *fmt, ...);
void func_00210F50(void *f)
{
    fiprintf(f, D_002A8AA8, D_003DD490.a, D_003DD490.b);
}
