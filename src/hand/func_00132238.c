/* OnBarrierXpNew: the base (0x1F4FB0), then a barrier whose frame binds the splice event 5 queues
 * TellBarrierContacts (D_002A4790) as a deferred call. SafeHouse port (barrier.cpp). */
struct PFN8 { int a; int b; };   /* a pointer to function, 8 bytes */
extern struct PFN8 D_002A4790;   /* TellBarrierContacts */
extern char g_sw[];
struct BARRIER { void *pframe; };   /* LO +0x0: its splice frame */
void func_001F4FB0(struct BARRIER *pbarrier);
void *PrefFindBinding(void *pframe, int n, int m) asm("PrefFindBinding__6CFrameUii");
void PostDeferredCall__FPvUi15PFNDEFERREDCALLi(void *psw, void *pv, struct PFN8 pfn, int n);
// name: SafeHouse port (OnBarrierXpNew)
void OnBarrierXpNew__FP3ALO(struct BARRIER *pbarrier)
{
    func_001F4FB0(pbarrier);
    if (pbarrier->pframe && PrefFindBinding(pbarrier->pframe, 5, 1))
        PostDeferredCall__FPvUi15PFNDEFERREDCALLi(g_sw, pbarrier, D_002A4790, 0);
}
