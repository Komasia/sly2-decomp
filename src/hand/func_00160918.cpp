#include "dmas.h"
extern "C" void func_00160918(DMAS *pdmas, QW *pqwStart, QW *pqwEnd)
{
    pdmas->AddDmaRefs((uint)((char *)pqwEnd - (char *)pqwStart + 15) >> 4, pqwStart);
}
