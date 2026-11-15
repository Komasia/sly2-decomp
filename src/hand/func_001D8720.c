/* SymFromName (SafeHouse savedata.cpp, orig 0x1D8720): a name's progress symbol (case-insensitive), -1 if none. */
#include "h3_progress.h"
unsigned int func_001D8640(char *pchz);
int strcasecmp(char *pchzA, char *pchzB);

// name: SafeHouse port (SymFromName)
int SymFromName__FP6LAYOUTPc(NAMETABLE *pnametable, char *pchz)
{
    unsigned int h = func_001D8640(pchz);
    NAME *pname;
    for (pname = pnametable->apname[h % CNAMEBUCKET]; pname; pname = pname->pnameNext) {
        if (pname->h == h && strcasecmp(pname->pchz, pchz) == 0)
            return pname->sym;
    }
    return -1;
}
