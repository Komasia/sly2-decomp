/* InitBarrier (cid 0x56, vt slot 7): InitSo, then flag bit 34 of +0x148: the barrier is its own physics root, so its
 * collision entries get their own attachment. SafeHouse port (barrier.cpp). */
struct BARRIER { char pad[0x148]; unsigned long grf; };
void InitSo__FP2SO(struct BARRIER *pbarrier);
void InitBarrier__FP7BARRIER(struct BARRIER *pbarrier)
{
    InitSo__FP2SO(pbarrier);
    pbarrier->grf |= 0x8000L << 19;   /* bit 34 */
}
