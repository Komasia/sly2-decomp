/* RenderRenderTargets: each owned render target gets its camera's view / projection for the scene (0x1BE6F0 over the
 * targets table D_003E1A78), then the scene's render pass (0x16E1A8) draws into them. */
struct SCENE;
struct RENDEROPTS;
extern char D_003E1A78[];   /* the render targets table */
void func_001BE6F0(void *prtgts, struct SCENE *pscene);
void func_0016E1A8(struct SCENE *pscene, struct RENDEROPTS *popts, int n);

// name: SafeHouse port (RenderRenderTargets)
void RenderRenderTargets__FP5SCENEP10RENDEROPTSi(struct SCENE *pscene, struct RENDEROPTS *popts, int n)
{
    func_001BE6F0(D_003E1A78, pscene);
    func_0016E1A8(pscene, popts, n);
}
