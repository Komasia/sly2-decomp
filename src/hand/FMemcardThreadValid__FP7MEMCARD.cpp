/* FMemcardThreadValid (Sly 1 memcard.c): does the memory card worker thread exist? */
#include "memcard.h"

int FMemcardThreadValid(MEMCARD *pmemcard)
{
    return pmemcard->threadId != -1;
}
