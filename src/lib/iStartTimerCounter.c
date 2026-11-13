// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
typedef struct { int x0; int x4; int id; int mode; long base; } Counter;
typedef struct { char pad[0x1C]; volatile int cur; } TimerSys;
extern TimerSys D_002C5A30;
long iGetTimerSystemTime(void);
void InsertAlarm(Counter *);
void SetNextComp(long);
int iStartTimerCounter(int id)
{
    Counter *p = (Counter *)(((unsigned int)id >> 10) << 6);
    long t;
    TimerSys *ts;
    if (id < 0 || (id & 0x3FF) != p->id)
        return 0x80008002;
    ts = &D_002C5A30;
    if (ts->cur == id)
        return 0x80000010;
    if (p->mode & 1)
        return 1;
    t = iGetTimerSystemTime();
    p->base = t;
    p->mode |= 1;
    if (p->mode & 2) {
        InsertAlarm(p);
        SetNextComp(t);
    }
    return 0;
}
