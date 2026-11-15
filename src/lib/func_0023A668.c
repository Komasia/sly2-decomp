// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
/* Timer handler behind every alarm (ps2sdk: AlarmHandler): call the user's alarm handler with the alarm id;
   if it returns 0 the alarm is finished, so put it back in the pool and return -1 (free the counter). */
typedef struct Alarm {
    struct Alarm *alarm_next;
    int timer_counter_id;
    int (*callback_handler)(int, int, int, void *);
    void *callback_handler_arg;
} Alarm;
extern Alarm * volatile D_0044E700;     /* g_pFreeAlarm */

int func_0023A668(int id, int scheduled, int actual, Alarm *alarm)
{
    int ret = alarm->callback_handler(((int)alarm << 4) | (id & 0xFE) | 1, scheduled, actual,
                                      alarm->callback_handler_arg);
    if (ret == 0) {
        Alarm *head = D_0044E700;
        D_0044E700 = alarm;
        alarm->alarm_next = head;
        alarm->timer_counter_id = 0;
        return -1;
    }
    return ret;
}
