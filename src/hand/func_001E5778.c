/* func_001E5778: whether the script has already been taken off its relay's script list (dlJsg). */
#include "relay.h"

int FFindDlEntry__FP2DLPv(DL *pdl, void *pv);

int func_001E5778(JSG *pjsg)
{
    return FFindDlEntry__FP2DLPv(&pjsg->prelay->dlJsg, pjsg) == 0;
}
