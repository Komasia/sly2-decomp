struct E { char pad[0x4C]; int n; };
extern int g_pdcToSpr;
extern int D_002C3C5C;
extern struct E D_003DD2C0[];
int sceDmaSync(int ch, int a, int b);
void func_00201998(void) { sceDmaSync(g_pdcToSpr, 0, 0); D_002C3C5C = 1 - D_002C3C5C; D_003DD2C0[D_002C3C5C].n = 2; }
