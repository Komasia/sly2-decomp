void func_00205478(void *p, int a, int b);
void func_00143EE0(void *p, int a, int b, int c);
void func_0019CD38(void *p, int a);
void func_001442D0(char *p, int a, int b)
{
    func_00205478(p, a, b);
    if (b) {
        if (++*(int *)(p + 0x12F4) == 1) {
            func_00143EE0(p, 0x60B, 9, 5);
            func_0019CD38(p + 0xF00, -1);
        }
    }
}
