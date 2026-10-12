#include "dmas.h"
extern QW D_002DF260[];
void BlastAqwGifsBothFrames(QW *aqw);
void ClearFrameBuffers()
{
    DMAS dmas;
    QW aqw[2];
    dmas.AllocStatic(2, aqw);
    dmas.AddDmaRefs(0x25, D_002DF260);
    dmas.AddDmaEnd();
    dmas.Detach(0, 0);
    BlastAqwGifsBothFrames(aqw);
}
