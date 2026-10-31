// SLY2_CC: tools/compilers/bundle/ee-gcc2.95.3-136
// SLY2_CFLAGS: -O2 -G0
typedef struct CB { void (*fn)(int, long); int pad; long arg; } CB;
typedef struct RPC { int x[16]; } RPC;
extern int *gSndCommandBuffePtr[2];
extern int gCommandBuffeBytesAvail[2];
extern CB *gSndCommandReturnDefPtr[2];
extern int *gReturnValuesPtr[2];
extern int gLoadBusy, D_002C46B8;
extern CB gLoadReturnDef;
extern int D_00443B80[], D_00444B80[], D_00447B80[], D_00447FC0[];
extern CB D_00445B80[], D_00446B80[];
extern RPC D_00443800, D_00448440;
extern int D_00448400[];
extern unsigned int gLoadReturnValue;
extern char D_002AA100[], D_002AA128[];
void func_0021EC18(const char *, ...);
void func_00236A60(int);
int func_002370A8(void *, int, int);
int func_002325E0(int, int, void *);

void func_002319E8(int flags)
{
    int i;
    int buf[2];

    gSndCommandBuffePtr[0] = D_00443B80;
    gSndCommandBuffePtr[1] = D_00444B80;
    gReturnValuesPtr[0] = D_00447B80;
    gReturnValuesPtr[1] = D_00447FC0;
    gSndCommandReturnDefPtr[0] = D_00445B80;
    gSndCommandReturnDefPtr[1] = D_00446B80;
    if (flags & 2)
        D_002C46B8 = 1;
    else
        D_002C46B8 = 0;
    func_00236A60(0);
    do {
        if (func_002370A8(&D_00443800, 0x123456, 0) < 0) {
            func_0021EC18(D_002AA100, D_002AA128, 0xB5);
            while (1)
                ;
        }
        i = 9999;
        while (i--)
            ;
    } while (!D_00443800.x[9]);
    gLoadBusy = 0;
    gLoadReturnDef.fn = 0;
    gLoadReturnDef.arg = 0;
    gLoadReturnValue = 0;
    do {
        if (func_002370A8(&D_00448440, 0x123457, 0) < 0) {
            func_0021EC18(D_002AA100, D_002AA128, 0xCA);
            while (1)
                ;
        }
        i = 9999;
        while (i--)
            ;
    } while (!D_00448440.x[9]);
    ((volatile int *)D_00448400)[0] = 0;
    ((volatile int *)D_00448400)[4] = 0;
    *D_00443B80 = 0;
    *D_00444B80 = 0;
    gCommandBuffeBytesAvail[0] = 0xFFC;
    buf[0] = (int)D_00448400;
    buf[1] = flags;
    gCommandBuffeBytesAvail[1] = 0xFFC;
    func_002325E0(0, 8, buf);
}
