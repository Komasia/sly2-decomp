/* CBinaryAsyncStream::Close (0x132688): close the host file, or wait for the disc read in flight (Sly 1 bas.c). */
#include "bas.h"

extern "C" int sceClose(int fd);
extern "C" int sceCdSync(int mode);

void CBinaryAsyncStream::Close()
{
    switch (m_bask)
    {
        case BASK_Host:
            if (m_fd >= 0)
                sceClose(m_fd);
            m_fd = -1;
            break;

        case BASK_Cd:
            if (FSpooling())
            {
                sceCdSync(0);
                FinishSpooling();
            }
            m_isector = 0;
            break;
    }

    m_bask = BASK_Nil;
}
