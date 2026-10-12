struct E { int a; int b; };
int func_00161F10(int x, struct E *ae, int cMax, int *pc, int a, int b)
{
    struct E *pe;
    if (*pc < cMax) {
        pe = &ae[(*pc)++];
        pe->a = a;
        pe->b = b;
        return 1;
    }
    return 0;
}
