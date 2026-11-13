// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
typedef struct Alarm {
    struct Alarm *next;
    volatile int id;
    void *func;
    void *arg;
} Alarm;
extern Alarm *D_0044E700;
int DIntr(void);
int EIntr(void);
int AllocTimerCounter(void);
int SetTimerHandler(int, long, void *, void *);
int func_0023A3A0(int);
int func_0023A668(int, int, int, Alarm *);
static inline Alarm *AllocAlarm(void)
{
    Alarm *p = D_0044E700;
    if (p)
        D_0044E700 = p->next;
    return p;
}
int SetTimerAlarm(long sched, void *func, void *arg)
{
    Alarm *p;
    int id;
    int st;
    if (func == 0)
        return 0x80000016;
    st = DIntr();
    p = AllocAlarm();
    if (p == 0) {
        if (st)
            EIntr();
        return 0x80008005;
    }
    id = AllocTimerCounter();
    if (id < 0) {
        Alarm *h = D_0044E700;
        D_0044E700 = p;
        p->next = h;
        p->id = 0;
        if (st)
            EIntr();
        return id;
    }
    p->func = func;
    p->arg = arg;
    p->id = id;
    SetTimerHandler(id, sched, func_0023A668, p);
    func_0023A3A0(id);
    if (st)
        EIntr();
    return ((int)p << 4) | (id & 0xFE) | 1;
}
