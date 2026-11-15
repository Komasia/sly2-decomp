// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
// name: libkernel TimerUSec2BusClock (sec, usec to bus clocks, used by DelayThread; suggested by l1)
unsigned long TimerUSec2BusClock(unsigned int sec, unsigned int usec)
{
    return (unsigned long)sec * 147456000 + (unsigned long)usec * 147456000 / 1000000;
}
