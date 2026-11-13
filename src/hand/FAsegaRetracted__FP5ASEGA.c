/* FAsegaRetracted: whether an animation segment player (ASEGA) has been retracted, i.e. is no longer in the list
 * of running ASEGAs (D_003E1218, which the ASEGA constructor func_0012F9B8 appends to).
 * name: SafeHouse port (asega.cpp "orig: 0x00131968"; spliceglue.cpp "EOPID126 -> 0x00131968 FAsegaRetracted"). */
struct ASEGA;
struct DL;
extern struct DL D_003E1218;   /* the running ASEGAs */
int FFindDlEntry(struct DL *pdl, void *pv) asm("FFindDlEntry__FP2DLPv");

int FAsegaRetracted__FP5ASEGA(struct ASEGA *pasega)
{
    return FFindDlEntry(&D_003E1218, pasega) == 0;
}
