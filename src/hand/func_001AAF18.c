/* func_001AAF18 (0x1AAF18): the memory card worker thread's entry (Sly 1 memcard.c): with the card semaphore held it
 * runs its MC method on the save manager D_002E65E0 and keeps the result, clears the method, marks the thread gone
 * (also D_004425D8), releases the semaphore and exits. */
#include "vtbl.h"
struct MEMCARD { int semaId; int threadId; VTENT pmf; int nResult; };
extern char g_mc[] __asm__("D_002E65E0");        /* the save manager (MC, include/h5_mc.h) */
extern int g_athidMemcard[] __asm__("D_004425D8"); /* the worker thread's id (-1 none) */
void WaitSema(int);
void SignalSema(int);
void ExitDeleteThread(void);
void *s1_memset(void *, int, unsigned int) asm("memset");
void func_001AAF18(struct MEMCARD *pmemcard)
{
    WaitSema(pmemcard->semaId);
    pmemcard->nResult = ((int (*)(void *))pmemcard->pmf.pfn)(g_mc + pmemcard->pmf.delta);
    s1_memset(&pmemcard->pmf, 0, sizeof(pmemcard->pmf));
    pmemcard->threadId = -1;
    g_athidMemcard[0] = -1;
    SignalSema(pmemcard->semaId);
    ExitDeleteThread();
}
