extern unsigned char D_002BE328[];
extern void *D_002DE9F0[];
void *func_0015EFA0(unsigned char ch)
{
    int i;
    for (i = 0; i < 2; i++)
        if (ch == D_002BE328[i])
            break;
    if (i < 2)
        return D_002DE9F0[i];
    return 0;
}
