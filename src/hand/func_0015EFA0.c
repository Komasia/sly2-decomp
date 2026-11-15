/* func_0015EFA0: the built-in font a rich text font code selects (D_002BE328: the codes of the two fonts), or 0. */
extern unsigned char D_002BE328[];
extern void *D_002DE9F0[];   /* the font table */
void *func_0015EFA0(unsigned char chCode)
{
    int ifont;
    for (ifont = 0; ifont < 2; ifont++)
        if (chCode == D_002BE328[ifont])
            break;
    if (ifont < 2)
        return D_002DE9F0[ifont];
    return 0;
}
