/* CByteQueue::FreeDrain (Sly 1 bq.c): return cb drained bytes (0: all of them) to the free space. */
#include "bq.h"

void CByteQueue::FreeDrain(int cb)
{
    if (cb == 0)
    {
        cb = m_cbDrain;
        if (cb == 0)
            return;
    }

    m_cbFree += cb;
    m_cbDrain -= cb;
}
