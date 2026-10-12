struct ThreadParam {
    int status; void *entry; void *stack; int stackSize; void *gpReg;
    int initPriority; int currentPriority; unsigned attr; unsigned option; int waitType; int waitId; int wakeupCount;
};
extern int D_004425D0[2];
extern char D_004425F0[];
extern char D_002E5270[];
void func_00160B70(void *);
int func_00234910(void);
void func_002348B0(int tid, int prio);
void *func_002333B4(void *p, int c, int n);
int func_00234820(struct ThreadParam *tp);

void func_0021F100(void)
{
    struct ThreadParam tp;
    int *ptid = D_004425D0;
    *ptid = func_00234910();
    func_002348B0(*ptid, 5);
    func_002333B4(&tp, 0, sizeof(tp));
    tp.stackSize = 0x1000;
    tp.stack = D_004425F0;
    tp.initPriority = 2;
    tp.gpReg = D_002E5270;
    tp.entry = func_00160B70;
    ptid[1] = func_00234820(&tp);
}
