struct BIG { int a[0x5408 / 4]; };
extern struct BIG *D_002DEB4C;
extern struct BIG D_003D4A60;
void func_001D54B8(void);
void func_001D8FF8(struct BIG *p);
void func_00166008(void)
{
    if (D_002DEB4C) {
        D_003D4A60 = *D_002DEB4C;
        D_002DEB4C = 0;
        func_001D54B8();
        func_001D8FF8(&D_003D4A60);
    }
}
