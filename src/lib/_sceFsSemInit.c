// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0 
// SLY2_ASM: gnu-reorder-db
struct SemaParam { int currentCount; int maxCount; int initCount; int numWaitThreads; unsigned int attr; unsigned int option; };
extern int D_002C4A84;      /* _sceFs_sema */
extern char D_002AAA98[];   /* semaphore option tag */
int CreateSema(struct SemaParam *);

/* _sceFsSemInit (libkernel fileio): create the fileio RPC semaphore once. */
void _sceFsSemInit(void)
{
    struct SemaParam p;
    if (D_002C4A84 == -1) {
        p.option = (unsigned int)D_002AAA98;
        p.initCount = 1;
        p.maxCount = 1;
        D_002C4A84 = CreateSema(&p);
    }
}
