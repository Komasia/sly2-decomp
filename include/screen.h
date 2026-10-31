/* Sly 1 screen.c TIMER: the on-screen countdown / stopwatch (partial; Sly 2's BLOT base is 0x64 bytes and not
 * mapped here). */
#ifndef SCREEN_H
#define SCREEN_H

enum TIMERS { TIMERS_Nil = -1, TIMERS_Expired = 0, TIMERS_Paused = 1, TIMERS_Running = 2, TIMERS_Max = 3 };

typedef struct TIMER {
    /* 0x00 */ char blot[0x64];        /* BLOT */
    /* 0x64 */ enum TIMERS timers;
    /* 0x68 */ float tTimers;          /* g_clock.tReal when timers last changed */
} TIMER;

#endif
