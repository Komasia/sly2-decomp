// SLY2_CC: tools/compilers/ee-gcc2.96
// SLY2_CFLAGS: -O2 -G0 -falign-jumps=1 -fno-schedule-insns
typedef volatile struct TC {
    struct TC *next;
    int pad4;
    int id;
    int xC;
    int x10, x14;
    long x18;
    int x20, x24;
    int x28;
} TC;
typedef struct {
    int x0, x4, x8;
    int seq;
    int count;
    TC *free;
} TS;
extern volatile TS D_002C5A30;
int iAllocTimerCounter(void)
{
    volatile TS *ts = &D_002C5A30;
    TC *p = ts->free;
    if (p == 0)
        return 0x80008005;
    ts->count++;
    p->x28 = 0;
    p->xC = 0;
    ts->free = p->next;
    p->x18 = 0;
    ts->seq++;
    p->id = ((ts->seq << 1) & 0x3FE) | 1;
    return ((int)p << 4) | p->id;
}
