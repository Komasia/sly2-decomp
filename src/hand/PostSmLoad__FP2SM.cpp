struct LO;
struct SMA { int oid; int a; int b; };
struct SM { char pad[0x74]; SMA *psma; };
struct G;
extern "C" {
extern G D_003DD490;
void PostLoLoad(LO *plo) asm("PostLoLoad__FP2LO"); /* PostLoLoad */
LO *func_0015E938(G *pg, int kind, int oid, SM *psm);
void func_001F0380(SM *psm, LO *plo, int a, int b);
}
void PostSmLoad(SM *psm)
{
    PostLoLoad((LO *)psm);
    if (psm->psma) {
        LO *plo = func_0015E938(&D_003DD490, 4, psm->psma->oid, psm);
        func_001F0380(psm, plo, psm->psma->a, psm->psma->b);
    }
}
