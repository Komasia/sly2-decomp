/* InitMemcard (Sly 1 memcard.c; Sly 2 sets the state field at +0x10 to 0x20 where Sly 1 used 0x22). */
#include "memcard.h"

int SemaCreate__Fii(int cInit, int cMax);

void InitMemcard__FP7MEMCARD(MEMCARD *pmemcard)
{
    pmemcard->semaId = SemaCreate__Fii(1, 1);
    pmemcard->threadId = -1;
    pmemcard->field_0x10 = 0x20;
}
