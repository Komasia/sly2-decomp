/* CreateMemcardThread (0x1AAF90, Sly 1 memcard.c): waits for any running card thread (SetMemcardThreadHighPrio),
 * stores the MC method to run, marks the result busy (0x21) and starts a thread (priority 3, a 16 KB stack at
 * D_002E2080) at func_001AAF18 with the MEMCARD as its argument; its id also goes to D_004425D8. */
#include "vtbl.h"
struct MEMCARD { int semaId; int threadId; VTENT pmf; int nResult; };
struct ThreadParam { int attr; void *entry; void *stack; int stackSize; void *gpReg; int initPriority; int currentPriority; unsigned int attr2; int option; int waitType; int waitId; int wakeupCount; };
extern char g_gp[] __asm__("D_002E5270");
extern char g_abMemcardStack[] __asm__("D_002E2080");
extern int g_athidMemcard[] __asm__("D_004425D8");
#define CB_MEMCARD_STACK 0x4000
#define MCR_BUSY 0x21
void func_001AAF18(struct MEMCARD *pmemcard);
void SetMemcardThreadHighPrio__FP7MEMCARD(struct MEMCARD *pmemcard);
void *s1_memset(void *p, int c, unsigned int n) asm("memset");
int CreateThread(struct ThreadParam *tp);
void StartThread_2355E0(int id, void *arg);
void CreateMemcardThread__FP7MEMCARDii(struct MEMCARD *pmemcard, VTENT pmf)
{
    struct ThreadParam tp;
    SetMemcardThreadHighPrio__FP7MEMCARD(pmemcard);
    pmemcard->pmf = pmf;
    pmemcard->nResult = MCR_BUSY;
    s1_memset(&tp, 0, sizeof(tp));
    tp.entry = func_001AAF18;
    tp.stack = g_abMemcardStack;
    tp.gpReg = g_gp;
    tp.stackSize = CB_MEMCARD_STACK;
    tp.initPriority = 3;
    pmemcard->threadId = CreateThread(&tp);
    g_athidMemcard[0] = pmemcard->threadId;
    StartThread_2355E0(pmemcard->threadId, pmemcard);
}
