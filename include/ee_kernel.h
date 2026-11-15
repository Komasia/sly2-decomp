/* ee_kernel.h - constants for the Sony EE kernel / libkernel code in src/lib.
 *
 * Only macros and plain types live here (no prototypes), so every src/lib file can include it without
 * changing its declarations. Names follow the public SDK documentation and the EE hardware manual;
 * the timer/alarm names follow the open-source ps2sdk reimplementation where Sony's are not public.
 */
#ifndef EE_KERNEL_H
#define EE_KERNEL_H

/* ---- FlushCache() operations ---- */
#define WRITEBACK_DCACHE  0
#define INVALIDATE_DCACHE 1
#define INVALIDATE_ICACHE 2

/* ---- COP0 Status register ---- */
#define COP0_STATUS_EIE 0x10000     /* master interrupt enable (EI/DI) */

/* ---- thread status (ThreadParam.status) ---- */
#define THS_RUN     0x01
#define THS_READY   0x02
#define THS_WAIT    0x04
#define THS_SUSPEND 0x08
#define THS_DORMANT 0x10

/* ---- INTC interrupt causes ---- */
#define INTC_TIM2 11

/* ---- EE timer 2 registers (KSEG1 copies are what SetT2 writes through) ---- */
#define T2_COUNT_ADDR 0x10001000
#define T2_MODE_ADDR  0x10001010
#define T2_COMP_ADDR  0x10001020
#define K_T2_COUNT_ADDR 0xB0001000
#define K_T2_MODE_ADDR  0xB0001010
#define K_T2_COMP_ADDR  0xB0001020
#define T2_COUNT (*(volatile unsigned int *)T2_COUNT_ADDR)
#define T2_MODE  (*(volatile unsigned int *)T2_MODE_ADDR)

/* Tn_MODE bits */
#define T_MODE_CLKS 0x003           /* clock select: BUSCLK, /16, /256, HBLNK */
#define T_MODE_ZRET 0x040           /* clear the counter on compare */
#define T_MODE_CUE  0x080           /* count-up enable */
#define T_MODE_CMPE 0x100           /* compare interrupt enable */
#define T_MODE_OVFE 0x200           /* overflow interrupt enable */
#define T_MODE_EQUF 0x400           /* compare flag (write 1 to clear) */
#define T_MODE_OVFF 0x800           /* overflow flag (write 1 to clear) */

/* ---- libkernel timer / alarm API ---- */
#define TIMER_COUNTER_COUNT 128     /* counters in the timer pool */
#define TIMER_ALARM_COUNT   64      /* alarms in the alarm pool */
#define TIMER_MIN_RESCHEDULE 0x3999 /* shortest interval a handler may ask for */
#define TIMER_COMP_MARGIN    0x7333 /* SetNextComp: closer events are merged / fired early */

#define TIMER_MODE_START   1        /* counter is running */
#define TIMER_MODE_HANDLER 2        /* counter has a handler and is on the alarm list */

/* timer ids are (counter pointer << 4) | key; counters are 64-byte aligned */
#define TIMER_ID_TO_PTR(id) (((unsigned int)(id) >> 10) << 6)
#define TIMER_ID_KEY_MASK   0x3FF

/* error codes returned by the timer / alarm / DelayThread API */
#define KE_EINVAL       0x80000016  /* bad argument (NULL handler) */
#define KE_EBUSY        0x80000010  /* counter is being handled right now */
#define KE_EINIT        0x80008001  /* timer already / not yet initialised */
#define KE_EID          0x80008002  /* bad timer or alarm id */
#define KE_ESEMAPHORE   0x80008003  /* CreateSema failed */
#define KE_ETIMER       0x80008005  /* no free counter / alarm */
#define KE_ECONTEXT     0x80008008  /* called with interrupts disabled */
#define KE_EINT_HANDLER 0x80009021  /* AddIntcHandler2 failed */

/* ---- DMA channel CHCR bits ---- */
#define D_CHCR_STR 0x100            /* channel busy / start */

#endif /* EE_KERNEL_H */
