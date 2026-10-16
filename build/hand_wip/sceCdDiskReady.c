// (Claude agent) libcdvd sceCdDiskReady: structure reconstructed (bind retry with TWO delay loops: after bind-error printf and after serve==0; fail path SignalSema + return mode==8?-1:6). -Os gives lui sN hoists but keeps li -1 inside delay loop (gas 'problematic short loop'); -O2 hoists -1 but has lui+daddu copies. Not matched.
// SLY2_CC: tools/compilers/bundle/ee-gcc2.95.3-114
// SLY2_CFLAGS: -Os -G0
// SLY2_ASM: gnu-reorg
// SLY2_SAVES: sd
typedef struct { int pad[9]; void *serve; int pad2[6]; } sceSifClientData;
extern int D_002C6750;
extern int D_002C6780;
extern int D_002C676C;
extern int D_002C6790;
extern sceSifClientData D_00450510;
extern int D_00450550[];
extern int D_002C7940[];
int printf(const char *fmt, ...);
int func_00239450(void);
int func_002394A0(void);
void func_00241A30(void);
int func_00234A70(int);
int func_00241F28(int);
void func_00236A60(int);
int func_002370A8(sceSifClientData *, unsigned int, int);
void func_0023B170(void *, int);
int func_00237288(void *cd, int fno, unsigned int mode, void *send, int ssize, void *recv, int rsize, void *end, void *earg);
int func_00234A40(int);

int sceCdDiskReady(int mode)
{
    int r;
    volatile int i;
    if (D_002C6750 > 0) printf("DiskReady 0\n");
    r = func_00239450();
    D_002C6780 = 1;
    if (r) func_002394A0();
    func_00241A30();
    if (func_00234A70(D_002C676C) != D_002C676C) return 6;
    if (func_00241F28(1)) goto fail;
    func_00236A60(0);
    if (D_002C6790 < 0) {
        while (1) {
            if (func_002370A8(&D_00450510, 0x8000059A, 0) < 0) {
                int j = 0x100000, k = -1;
                if (D_002C6750 > 0) printf("Bind error\n");
                do __asm__ volatile(""); while (--j != k);
                continue;
            }
            if (D_00450510.serve != 0) break;
            {
                int j = 0x100000, k = -1;
                do __asm__ volatile(""); while (--j != k);
            }
        }
        D_002C6790 = 0;
    }
    D_00450550[0] = mode;
    func_0023B170(D_00450550, 4);
    if (func_00237288(&D_00450510, 0, 0, D_00450550, 4, D_002C7940, 4, 0, 0) < 0) {
fail:
        func_00234A40(D_002C676C);
        if (mode == 8) return -1;
        return 6;
    }
    if (D_002C6750 > 0) printf("DiskReady ended\n");
    r = *(int *)((unsigned int)D_002C7940 | 0x20000000);
    func_00234A40(D_002C676C);
    return r;
}
