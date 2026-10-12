struct A { char pad[0xA0]; int f; };
void func_001FCF88(void);
void func_002330D0(int id, int n, int a, int b, int c, int d, int e, void (*pfn)(void), long p);
void func_001FDBA8(struct A *p)
{
    if (!p->f) {
        p->f = 1;
        func_002330D0(0x524B5553, 0xC, 0, 0, 0, 0, 0, func_001FCF88, (long)p);
    }
}
