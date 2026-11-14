/* libmpeg (a callback with no direct callers): the IPU DMA of the decoder's internal data (+0x40, its +0x68 state)
 * stopped (sceIpuStopDMA); 1. */
typedef struct SCEMPEG {
    /* 0x00 */ char pad0[0x40];
    /* 0x40 */ char *sys;
} SCEMPEG;

void sceIpuStopDMA(void *pstate);

int func_0024B9A0(SCEMPEG *mp)
{
    sceIpuStopDMA(mp->sys + 0x68);
    return 1;
}
