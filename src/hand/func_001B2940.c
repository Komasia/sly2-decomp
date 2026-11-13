struct ThreadParam { int status; void (*entry)(void *); void *stack; int stackSize; void *gpReg; int initPriority; int currentPriority; unsigned attr; unsigned option; int waitType; int waitId; int wakeupCount; };
struct G { char pad[0x114]; int n114; char pad1[0x23C - 0x118]; int n23C; };
extern struct G D_002F66B0;
extern char D_002F6900[];
extern char D_002E5270[];
extern int D_004425DC;
int SemaCreate(int a, int b) asm("SemaCreate__Fii");
void *s1_memset(void *pv, int c, int cb);
int CreateThread(struct ThreadParam *ptp);
int StartThread_002355E0(int id, void *arg);
void func_001B2828(void *);
void func_001B2940(void)
{
    struct ThreadParam tp;
    D_002F66B0.n23C = SemaCreate(0, 1);
    D_002F66B0.n114 = 0;
    s1_memset(&tp, 0, sizeof(tp));
    tp.entry = func_001B2828;
    tp.stack = D_002F6900;
    tp.gpReg = D_002E5270;
    tp.stackSize = 0x1000;
    tp.initPriority = 2;
    D_004425DC = CreateThread(&tp);
    StartThread_002355E0(D_004425DC, 0);
}
