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
void _InitSys(void)
{
    supplement_crt0();
    InitSystemCallTableAddress();
    InitAlarm();
    InitTimer(2);
    StartTimerSystemTime();
    InitThread();
    InitExecPS2();
    InitTLBFunctions();
    func_0023A8E8();
}
