/* RenderFrame__FP3FRMi (Sly 1 frm.c RenderFrame): render a frame: prepare the GS for it, send its VIF chain and, when
 * fRenderGifs, its GIF chain, each waiting for the GS to finish. */
struct FRM { int cqwGifs; void *aqwGifs; char pad[0x24 - 8]; void *aqwVifsRender; };
extern void *g_pdcVif1;
extern void *g_pdcGif;
void func_001EE7B0(struct FRM *pfrm, int fRenderGifs);
void func_00170048(void);
void SendDmaSyncGsFinish__FP10sceDmaChanP2QW(void *pch, void *pqw);
// name: Sly 1 frm.c RenderFrame(FRM *, fRenderGifs) (suggested by h2)
void RenderFrame__FP3FRMi(struct FRM *pfrm, int fRenderGifs)
{
    func_001EE7B0(pfrm, fRenderGifs);
    func_00170048();
    SendDmaSyncGsFinish__FP10sceDmaChanP2QW(g_pdcVif1, pfrm->aqwVifsRender);
    if (fRenderGifs)
        SendDmaSyncGsFinish__FP10sceDmaChanP2QW(g_pdcGif, pfrm->aqwGifs);
}
