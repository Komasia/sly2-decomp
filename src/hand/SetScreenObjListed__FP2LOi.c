/* SetScreenObjListed: a screen object's membership in the separately drawn screen-object list (the DL D_003E1060):
 * 0 listed, other values not. Source: SafeHouse port (screenrt.cpp). */
struct LO {
    /* 0x00 */ char pad0[0xa8];
    /* 0xa8 */ int nList;   /* 0: in the list */
};
extern char D_003E1060[];   /* the DL of listed screen objects */
int FFindDlEntry__FP2DLPv(void *pdl, void *pv);
void RemoveDlEntry__FP2DLPv(void *pdl, void *pv);
void AppendDlEntry__FP2DLPv(void *pdl, void *pv);

// name: SafeHouse port (SetScreenObjListed)
void SetScreenObjListed__FP2LOi(struct LO *plo, int n)
{
    int nOld = plo->nList;
    if (nOld != n) {
        if (nOld == 0 && FFindDlEntry__FP2DLPv(D_003E1060, plo))
            RemoveDlEntry__FP2DLPv(D_003E1060, plo);
        plo->nList = n;
        if (n == 0 && !FFindDlEntry__FP2DLPv(D_003E1060, plo))
            AppendDlEntry__FP2DLPv(D_003E1060, plo);
    }
}
