/* func_0015EF00: start up the fonts: build the built-in ones, then make the first the current font (D_002DE760,
 * Sly 1 g_pfont). */
extern void *D_002DE9F0[];   /* the font table, by font index */
extern void *D_002DE760;     /* the current font */
void func_0015EF30(void);
void func_0015EF00(void)
{
    func_0015EF30();
    D_002DE760 = D_002DE9F0[0];
}
