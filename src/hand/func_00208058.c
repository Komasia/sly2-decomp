struct E { int a, b, c, d; };
void func_00207F50(void *p, int mask, int b, int d, struct E *records);
void func_00208058(char *p, int mask, int b, int d)
{
    func_00207F50(p, mask, b, d, (struct E *)(p + 0xA70));
}
