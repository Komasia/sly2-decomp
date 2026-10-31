/* CBinaryAsyncStream::FOpenFile (0x132600): open a catalog file; only disc locations can be opened. */
#include "bas.h"

bool CBinaryAsyncStream::FOpenFile(CFileLocation *pfl)
{
    bool fOpen = false;

    if (pfl->m_kind == 2)
        fOpen = FOpenSector(pfl->m_fcl.isector, pfl->m_fcl.cb);
    return fOpen;
}
