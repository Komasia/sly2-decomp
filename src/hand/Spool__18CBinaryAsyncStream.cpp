/* CBinaryAsyncStream::Spool (0x132930): advance to the next chunk (Sly 1 bas.c). Host reads are synchronous, so
 * the read is started first; a disc stream takes the chunk already in flight and starts the next one. */
#include "bas.h"

void CBinaryAsyncStream::Spool()
{
    switch (m_bask)
    {
        case BASK_Host:
            StartSpooling();
            FinishSpooling();
            break;

        case BASK_Cd:
            FinishSpooling();
            StartSpooling();
            break;
    }
}
