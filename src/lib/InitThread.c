// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
#include "ee_kernel.h"
/* InitThread (libkernel): start the priority-0 "top" thread that carries out WakeupThread /
   RotateThreadReadyQueue / SuspendThread requests posted from interrupt handlers (see topThread).
   Returns the top thread's id, or -1. */
typedef struct { int currentCount; int maxCount; int initCount; int numWaitThreads; unsigned int attr; unsigned int option; } SemaParam;
typedef struct { int status; void *entry; void *stack; int stackSize; void *gpReg; int initPriority; int currentPriority; unsigned int attr; unsigned int option; int waitType; int waitId; int wakeupCount; } ThreadParam;
typedef struct { int requestOut; int requestIn; } TopArg;     /* head of topThread's request ring */
extern char D_002AA7D8[];       /* "SceKerneltopThread" */
extern char D_00448540[];       /* top thread stack, 0x400 bytes */
extern char D_002E5270[];       /* _gp */
extern int D_00448940;          /* request semaphore */
extern TopArg D_00448948;       /* request ring */
extern int D_002C49E8;          /* top thread id */
int CreateSema(SemaParam *);
int DeleteSema(int);
int CreateThread(ThreadParam *);
int StartThread_2355E0(int, void *);
int GetThreadId(void);
int ChangeThreadPriority(int, int);
void topThread(void *);

int InitThread(void)
{
    ThreadParam thread_param;
    SemaParam sema_param;
    char *name;
    if (D_002C49E8 > 0)
        goto fail;
    {
        name = D_002AA7D8;
        sema_param.maxCount = 0xFF;
        sema_param.initCount = 0;
        sema_param.option = (unsigned int)name;
        D_00448940 = CreateSema(&sema_param);
        if (D_00448940 < 0)
            goto fail;
        thread_param.entry = topThread;
        thread_param.stack = D_00448540;
        thread_param.stackSize = 0x400;
        thread_param.gpReg = D_002E5270;
        thread_param.option = (unsigned int)name;
        thread_param.initPriority = 0;
        D_002C49E8 = CreateThread(&thread_param);
        if (D_002C49E8 < 0) {
            DeleteSema(D_00448940);
        fail:
            return -1;
        }
        D_00448948.requestOut = 0;
        D_00448948.requestIn = 0;
        StartThread_2355E0(D_002C49E8, &D_00448948);
        ChangeThreadPriority(GetThreadId(), 1);
    }
    return D_002C49E8;
}
