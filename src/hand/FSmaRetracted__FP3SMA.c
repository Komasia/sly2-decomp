/* FSmaRetracted: a state machine player is retracted when it is no longer in the list of playing ones (the DL
 * D_003E126C). */
struct SMA;
extern char D_003E126C[];   /* the playing SMAs */
int FFindDlEntry__FP2DLPv(void *pdl, void *pv);

// name: SafeHouse port (FSmaRetracted, smrun.cpp)
int FSmaRetracted__FP3SMA(struct SMA *psma)
{
    return FFindDlEntry__FP2DLPv(D_003E126C, psma) == 0;
}
