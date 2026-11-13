/* A render target kind (SafeHouse render.cpp: kinds 4 / 6, 0x16E3C8's GS block D_002DF700, FBA 1): the base 0x16E1A8,
 * then 0x16E318(p, 2, D_002DF700). */
extern char D_002DF700[];   /* the GS block */
void func_0016E1A8(void *prt);
void func_0016E318(void *prt, int n, void *pgs);

void func_0016E3C8(void *prt)
{
    func_0016E1A8(prt);
    func_0016E318(prt, 2, D_002DF700);
}
