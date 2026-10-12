struct ZPR { char ab[0x630]; };
struct F { char ab[0x140]; };
extern struct F D_002DE770[];
extern int D_002BE320[];
void func_001703F8(struct ZPR *pzpr, int a, int b);
void func_0015F710(struct F *pf, int n, struct ZPR *pzpr);
void func_0015EF30(void)
{
    struct ZPR zpr;
    int i;
    func_001703F8(&zpr, 0x1000, 0x1800);
    for (i = 0; i < 2; i++) {
        int n = D_002BE320[i];
        func_0015F710(&D_002DE770[i], n, &zpr);
    }
}
