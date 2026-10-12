struct E { char pad[0x40]; };
extern struct E *D_003E1C40;
struct E *func_00210990(int i)
{
    if (i == -1)
        return 0;
    return &D_003E1C40[i];
}
