struct ThreadParam {
    int status; void *entry; void *stack; int stackSize; void *gpReg;
    int initPriority; int currentPriority; unsigned attr; unsigned option; int waitType; int waitId; int wakeupCount;
};
extern int D_004425D0[2];
extern char D_004425F0[];
extern char D_002E5270[];
void func_00160B70(void *);
int GetThreadId(void);
void ChangeThreadPriority(int tid, int prio);
void *s1_memset(void *p, int c, int n) asm("memset");
int CreateThread(struct ThreadParam *tp);

void StartupThread__Fv(void)
{
    struct ThreadParam tp;
    int *ptid = D_004425D0;
    *ptid = GetThreadId();
    ChangeThreadPriority(*ptid, 5);
    s1_memset(&tp, 0, sizeof(tp));
    tp.stackSize = 0x1000;
    tp.stack = D_004425F0;
    tp.initPriority = 2;
    tp.gpReg = D_002E5270;
    tp.entry = func_00160B70;
    ptid[1] = CreateThread(&tp);
}
