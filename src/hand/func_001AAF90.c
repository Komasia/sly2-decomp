struct PMF { short delta; short pad; int (*pfn)(void *); };
struct S { int x0; int x4; struct PMF pmf; int x10; };
struct ThreadParam { int attr; void *entry; void *stack; int stackSize; void *gpReg; int initPriority; int currentPriority; unsigned int attr2; int option; int waitType; int waitId; int wakeupCount; };
extern char D_002E5270[], D_002E2080[];
extern int D_004425D8[];
void func_001AAF18(struct S *s);
void SetMemcardThreadHighPrio__FP7MEMCARD(struct S *s);
void *s1_memset(void *p, int c, unsigned int n) asm("memset");
int CreateThread(struct ThreadParam *tp);
void StartThread_2355E0(int id, void *arg);
void CreateMemcardThread__FP7MEMCARDii(struct S *s, struct PMF pmf)
{
    struct ThreadParam tp;
    SetMemcardThreadHighPrio__FP7MEMCARD(s);
    s->pmf = pmf;
    s->x10 = 0x21;
    s1_memset(&tp, 0, sizeof(tp));
    tp.entry = func_001AAF18;
    tp.stack = D_002E2080;
    tp.gpReg = D_002E5270;
    tp.stackSize = 0x4000;
    tp.initPriority = 3;
    s->x4 = CreateThread(&tp);
    D_004425D8[0] = s->x4;
    StartThread_2355E0(s->x4, s);
}
