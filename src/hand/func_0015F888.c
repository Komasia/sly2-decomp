/* func_0015F888: register a font in the font table (D_002DE9F0) under its index (its first field). */
extern void *D_002DE9F0[];
struct CFontBrx { int ifont; };
void func_0015F888(struct CFontBrx *pfont)
{
    D_002DE9F0[pfont->ifont] = pfont;
}
