/* func_001A53E0 (0x1A53E0): frees an LO's root record (+0x14, the LOROOT): out of the world's root list (SW +0x2C)
 * if in it, dequeued (DequeueLoRoot), returned to its slot heap (SW +0x398C) and cleared. */
extern char g_sw[];
struct S { char pad[0x14]; void *ploroot; };
#define IB_SW_DL_ROOT 0x2C          /* SW +0x2C: the roots' list */
#define IB_SW_SLOTHEAP_ROOT 0x398C  /* SW +0x398C: the LOROOT slot heap */
int FFindDlEntry__FP2DLPv(void *, void *);
void RemoveDlEntry__FP2DLPv(void *, void *);
void DequeueLoRoot__FP2SWP2LO(void *, void *);
void func_0011CD98(void *, void *);
void func_001A53E0(struct S *plo)
{
    char *pdl = g_sw + IB_SW_DL_ROOT;
    if (FFindDlEntry__FP2DLPv(pdl, plo->ploroot))
        RemoveDlEntry__FP2DLPv(pdl, plo->ploroot);
    DequeueLoRoot__FP2SWP2LO(g_sw, plo->ploroot);
    func_0011CD98(g_sw + IB_SW_SLOTHEAP_ROOT, plo->ploroot);
    plo->ploroot = 0;
}
