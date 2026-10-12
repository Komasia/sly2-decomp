struct CLK { char pad[0x18]; float af[9]; };
extern struct CLK D_002DDED0;
void func_0014D1F8(void *p);
void func_0014D068(int *p)
{
    *p = 0;
    D_002DDED0.af[0] = 1.0f;
    D_002DDED0.af[1] = 1.0f;
    D_002DDED0.af[2] = 1.0f;
    D_002DDED0.af[5] = 1.0f;
    D_002DDED0.af[6] = 1.0f;
    D_002DDED0.af[8] = 1.0f;
    D_002DDED0.af[7] = 1.0f;
    D_002DDED0.af[4] = 1.0f;
    func_0014D1F8(p);
}
