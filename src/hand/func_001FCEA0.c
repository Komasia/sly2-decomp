struct G { char pad[0x13C]; float a[8][4]; float g1BC; float b[4]; char pad2[0x1F0 - 0x1D0]; long l1F0; long l1F8; };
extern struct G D_003DD040;
struct CLOCK;
extern struct CLOCK D_002DDED0;
void func_002319E8(int);
int func_00233048(int, int, int, int, int, int, int);
long func_0014D240(struct CLOCK *);
void func_001FCEA0(void)
{
    int i, j;
    long t;
    func_002319E8(2);
    (void)func_00233048(0x524B5553, 0, 0, 0, 0, 0, 0);
    D_003DD040.g1BC = 1.0f;
    for (i = 0; i < 4; i++) {
        D_003DD040.b[i] = 1.0f;
        for (j = 0; j < 8; j++) D_003DD040.a[j][i] = 1.0f;
    }
    t = func_0014D240(&D_002DDED0);
    D_003DD040.l1F0 = t;
    D_003DD040.l1F8 = t;
}
