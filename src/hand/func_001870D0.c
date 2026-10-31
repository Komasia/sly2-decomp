extern int g_grfjoyt, D_002DFBC4, D_002E0CBC;
void func_001870D0(void)
{
    int v = D_002DFBC4;
    if (v & 0x10) g_grfjoyt = 5;
    else if (v & 0xC) g_grfjoyt = 0;
    else if (v & 1) g_grfjoyt = 5;
    else if (v & 2) g_grfjoyt = 4;
    else g_grfjoyt = 7;
    if (!(g_grfjoyt & 2)) D_002E0CBC = 0xFFFF;
}
