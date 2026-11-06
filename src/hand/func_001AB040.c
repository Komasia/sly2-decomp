/* SetMemcardThreadHighPrio (Sly 1 memcard.c): raise the worker thread to priority 1 if it exists, then wait for
 * (and release) the memory card semaphore. */
#include "memcard.h"

int FMemcardThreadValid__FP7MEMCARD(MEMCARD *pmemcard);
int ChangeThreadPriority(int thid, int prio);
int WaitSema(int sema);
int SignalSema(int sema);

void SetMemcardThreadHighPrio__FP7MEMCARD(MEMCARD *pmemcard)
{
    if (FMemcardThreadValid__FP7MEMCARD(pmemcard)) {
        ChangeThreadPriority(pmemcard->threadId, 1);
    }
    WaitSema(pmemcard->semaId);
    SignalSema(pmemcard->semaId);
}
