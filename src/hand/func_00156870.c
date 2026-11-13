/* class: NOISE (SafeHouse ainoise.h FNoiseLive, orig 0x156870 inverted): the noise is no longer in the live list
 * D_003E148C. */
struct DL;
struct NOISE;
extern struct DL D_003E148C;   /* the live noises */
int FFindDlEntry__FP2DLPv(struct DL *pdl, void *pv);

int func_00156870(struct NOISE *pnoise)
{
    return FFindDlEntry__FP2DLPv(&D_003E148C, pnoise) == 0;
}
