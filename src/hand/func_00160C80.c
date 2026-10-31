struct S { int f0; void *f4; char pad[0x24 - 8]; void *f24; };
extern void *g_pdcVif1;
extern void *g_pdcGif;
void func_001EE7B0(struct S *p, int f);
void func_00170048(void);
void SendDmaSyncGsFinish__FP10sceDmaChanP2QW(void *pch, void *pqw);
void func_00160C80(struct S *p, int f)
{
    func_001EE7B0(p, f);
    func_00170048();
    SendDmaSyncGsFinish__FP10sceDmaChanP2QW(g_pdcVif1, p->f24);
    if (f)
        SendDmaSyncGsFinish__FP10sceDmaChanP2QW(g_pdcGif, p->f4);
}
