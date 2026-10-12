struct M { float a[16]; };
extern struct M D_002C44F0;
void func_002333B4(void *p, int c, int n);
struct M *func_001A6B30(void *unused, struct M *pm)
{
    if (pm) {
        func_002333B4(pm, 0, 0x40);
        pm->a[0] = pm->a[5] = pm->a[10] = pm->a[15] = 1.0f;
    }
    return &D_002C44F0;
}
