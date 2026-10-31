/* CBinaryAsyncStream::FSpoolingComplete (0x1327E0): has the read in flight finished (Sly 1 bas.c)? Only asked once the
 * current chunk is used up. A failed read is dropped. */
#include "bas.h"

extern "C" int sceIoctl(int fd, int req, void *pv);
extern "C" int sceCdSync(int mode);
extern "C" int sceCdGetError(void);

bool CBinaryAsyncStream::FSpoolingComplete()
{
    int status = 0;
    bool fComplete = false;

    if (m_cb == m_ibCur && FSpooling())
    {
        switch (m_bask)
        {
            case BASK_Host:
            {
                int fExecuting;
                status = sceIoctl(m_fd, 1, &fExecuting);
                fComplete = (fExecuting == 0);
                break;
            }
            case BASK_Cd:
            {
                fComplete = (sceCdSync(1) == 0);
                if (fComplete)
                {
                    status = sceCdGetError();
                }
                break;
            }
        }
    }

    if (status)
    {
        m_cbSpooling = 0;
        m_pbSpooling = 0;
        fComplete = false;
    }

    return fComplete;
}
