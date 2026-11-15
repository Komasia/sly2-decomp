// SLY2_CC: tools/compilers/bundle/ee-gcc2.95.3-114
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
// SLY2_SAVES: sd
#include "ee_kernel.h"
/* DelayThread (libkernel): sleep the calling thread for `usec` microseconds. A one-shot timer alarm signals a
   private semaphore that the thread waits on. */
typedef struct { int currentCount; int maxCount; int initCount; int numWaitThreads; unsigned int attr; unsigned int option; } SemaParam;
extern char D_002AA7F0[];   /* semaphore option tag (a name string) */
int CreateSema(SemaParam *);
int DeleteSema(int);
int WaitSema(int);
long TimerUSec2BusClock(int, int);   /* microseconds -> bus clocks (TimerUSec2BusClock) */
int SetTimerAlarm(long, void *, int);
int _DelayThreadHandler(int, unsigned short, void *);

int DelayThread(int usec)
{
    SemaParam sema_param;
    int sema;
    int alarm;
    int status;
    __asm__ volatile("mfc0 %0, $12" : "=r"(status));
    if ((status & COP0_STATUS_EIE) == 0)
        return KE_ECONTEXT;
    sema_param.maxCount = 1;
    sema_param.option = (unsigned int)D_002AA7F0;
    sema_param.initCount = 0;
    sema = CreateSema(&sema_param);
    if (sema < 0)
        return KE_ESEMAPHORE;
    alarm = SetTimerAlarm(TimerUSec2BusClock(0, usec), _DelayThreadHandler, sema);
    if (alarm >= 0) {
        WaitSema(sema);
        DeleteSema(sema);
        return 0;
    }
    DeleteSema(sema);
    return alarm;
}
