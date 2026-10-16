// WIP (Claude agent): 3/75 diffs - only arg-setup schedule before the SetTimerHandler call (target a2,a1,a0; ours a0 first). iSetTimerAlarm with the same block matches. Tried decl orders, store orders, prototypes, -fstrict-aliasing, 136.
// SLY2_CC: tools/compilers/bundle/ee-gcc2.95.3-114
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
// SLY2_SAVES: sd
typedef struct Alarm {
    struct Alarm *next;
    volatile int id;
    void *func;
    void *arg;
} Alarm;
extern Alarm *D_0044E700;
int func_00239450(void);
int func_002394A0(void);
int func_0023A298(void);
int func_0023A518(int, long, void *, void *);
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
    st = func_00239450();
    p = AllocAlarm();
    if (p == 0) {
        if (st)
            func_002394A0();
        return 0x80008005;
    }
    id = func_0023A298();
    if (id < 0) {
        Alarm *h = D_0044E700;
        D_0044E700 = p;
        p->next = h;
        p->id = 0;
        if (st)
            func_002394A0();
        return id;
    }
    p->func = func;
    p->arg = arg;
    p->id = id;
    func_0023A518(id, sched, func_0023A668, p);
    func_0023A3A0(id);
    if (st)
        func_002394A0();
    return ((int)p << 4) | (id & 0xFE) | 1;
}
