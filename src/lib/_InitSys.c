// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
void supplement_crt0(void);
void InitSystemCallTableAddress(void);
void InitAlarm(void);
void InitTimer(int);
void StartTimerSystemTime(void);
void InitThread(void);
void InitExecPS2(void);
void InitTLBFunctions(void);
void func_0023A8E8(void);

/* _InitSys (libkernel): runtime start-up called from crt0: locate the syscall table, install the kernel patches
   and start the timer, alarm and top-thread services. */
void _InitSys(void)
{
    supplement_crt0();
    InitSystemCallTableAddress();
    InitAlarm();
    InitTimer(2);   /* T2 counts BUSCLK/256 */
    StartTimerSystemTime();
    InitThread();
    InitExecPS2();
    InitTLBFunctions();
    func_0023A8E8();
}
