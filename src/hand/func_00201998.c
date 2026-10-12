struct E { char pad[0x4C]; int n; };
extern int D_002DE5A0;
extern int D_002C3C5C;
extern struct E D_003DD2C0[];
int func_002417F0(int ch, int a, int b);
void func_00201998(void) { func_002417F0(D_002DE5A0, 0, 0); D_002C3C5C = 1 - D_002C3C5C; D_003DD2C0[D_002C3C5C].n = 2; }
