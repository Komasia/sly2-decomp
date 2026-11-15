/* FUN_0018b930 (0x1AAB68): sceMcSync's state as a message id: 0x21 still running (0), 0x22 done (1), 0x20 no
 * call (-1), else 0x1F. */
int FUN_0018b930(int n)
{
    switch (n) {
    case 0: return 0x21;
    case 1: return 0x22;
    case -1: return 0x20;
    }
    return 0x1F;
}
