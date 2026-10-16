struct E { int a, b, c, d; };
void func_00207EB8(void *p, int mask, int b, int d, struct E *records);
void func_00208078(char *p, int mask, int b, int d)
{
    func_00207EB8(p, mask, b, d, (struct E *)(p + 0x8D0));
}
