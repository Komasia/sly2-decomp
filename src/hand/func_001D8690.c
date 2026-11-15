/* class: progress name table (LoadProgressFromBrx 0x1D7B88): add a name with its symbol - the next pool entry (taken
 * from the end) is linked at the front of its hash bucket. */
#include "h3_progress.h"
unsigned int func_001D8640(char *pchz);

void func_001D8690(NAMETABLE *pnametable, char *pchz, int sym)
{
    unsigned int h = func_001D8640(pchz);
    unsigned int ibucket = h % CNAMEBUCKET;
    NAME *pname = &pnametable->anamePool[pnametable->cnameFree - 1];
    pnametable->cnameFree--;
    pname->pchz = pchz;
    pname->sym = sym;
    pname->h = h;
    pname->pnameNext = pnametable->apname[ibucket];
    pnametable->apname[ibucket] = pname;
}
