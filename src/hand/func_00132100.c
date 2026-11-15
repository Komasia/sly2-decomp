/* PostBarrierLoad: the base post-load (0x1F36A8), then a barrier with collision entries (+0xE8) gets the world's
 * collision filter recomputed for it. */
struct BARRIER { char pad[0xe8]; int psoe; };
extern char g_sw[];
void func_001F36A8(struct BARRIER *pbarrier);
void RecalcSwOxfFilterForObject__FP2SWP2SO(void *psw, struct BARRIER *pbarrier);
void PostBarrierLoad__FP7BARRIER(struct BARRIER *pbarrier)
{
    func_001F36A8(pbarrier);
    if (pbarrier->psoe)
        RecalcSwOxfFilterForObject__FP2SWP2SO(g_sw, pbarrier);
}
