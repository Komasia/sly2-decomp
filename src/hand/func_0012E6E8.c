extern char D_002DDF40[];
void func_001A5848(void *p);
void func_0014E4C8(void *a, int b, int c, void *d, int e, void *f);
typedef struct T { char pad[0x124]; int f; } T;
void func_0012E6E8(T *t)
{
    func_001A5848(t);
    if (t->f)
        func_0014E4C8(D_002DDF40, 15, 10, D_002DDF40 + 0x4A8, 0, t);
}
