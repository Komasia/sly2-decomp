/* AddLaserAttachment (vt slot 53): adds the laser's bound-box attachment (func_001F56F8, SafeHouse PoxaAddSw) and
 * flags it 0x20: the laser's endpoint bounds do not prune the other shape's BSP. */
typedef struct OXA { char unk_0x0[0x70]; unsigned long grf; } OXA;   /* field: SafeHouse port */
#define GRFOXA_NoBspPrune 0x20
OXA *func_001F56F8(void *palo);
// name: SafeHouse port (AddLaserAttachment)
OXA *AddLaserAttachment__FP3ALO(void *plaser) {
    OXA *poxa = func_001F56F8(plaser);
    poxa->grf |= GRFOXA_NoBspPrune;
    return poxa;
}
