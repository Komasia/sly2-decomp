// (Claude agent) twin of sceCdDiskReady (retry counter, falls back to sceCdDiskReady). 80/136 diffs: -Os gnu-reorg; goto-bind loop gives target block order. Left: target hoists hi(cd)=s5 and keeps mode in s2/cnt in s1, cnt+1 into v0 before delay loop.
// SLY2_CC: tools/compilers/bundle/ee-gcc2.95.3-114
// SLY2_CFLAGS: -Os -G0
// SLY2_ASM: gnu-reorg
// SLY2_SAVES: sd
typedef struct { int pad[9]; void *serve; int pad2[6]; } sceSifClientData;
extern int D_002C6750;
extern int D_002C6780;
extern volatile int D_002C6770;
extern int D_002C6790;
extern sceSifClientData D_00450510;
extern int D_00450550[];
extern int D_002C81C0[];
int printf(const char *fmt, ...);
int func_00239450(void);
int func_002394A0(void);
void func_00241A30(void);
int func_00234A70(int);
void func_00236A60(int);
int func_002370A8(sceSifClientData *, unsigned int, int);
void func_0023B170(void *, int);
int func_00237288(void *cd, int fno, unsigned int mode, void *send, int ssize, void *recv, int rsize, void *end, void *earg);
int func_00234A40(int);
int sceCdDiskReady(int mode);

int sceCdDiskReady_2425F0(int mode)
{
    int r;
    int cnt;
    if (D_002C6750 > 0) printf("NEW DiskReady Call\n");
    func_00241A30();
    if (func_00234A70(D_002C6770) != D_002C6770) {
        if (mode == 8) return -1;
        return 6;
    }
    func_00236A60(0);
    cnt = 0;
    if (D_002C6790 < 0) {
        goto bind;
        do {
            if (cnt > 0x10) {
                func_00234A40(D_002C6770);
                return sceCdDiskReady(mode);
            }
            cnt++;
            {
                int j = 0x100000, k = -1;
                do __asm__ volatile(""); while (--j != k);
            }
        bind:
            if (func_002370A8(&D_00450510, 0x8000059C, 0) < 0) {
                int j = 0x100000, k = -1;
                if (D_002C6750 > 0) printf("Libcdvd bind err CdDiskReady\n");
                do __asm__ volatile(""); while (--j != k);
                goto bind;
            }
        } while (D_00450510.serve == 0);
        D_002C6790 = 0;
    }
    r = func_00239450();
    D_002C6780 = 0;
    if (r) func_002394A0();
    D_00450550[0] = mode;
    func_0023B170(D_00450550, 4);
    if (func_00237288(&D_00450510, 0, 0, D_00450550, 4, D_002C81C0, 4, 0, 0) < 0) {
        func_00234A40(D_002C6770);
        if (mode == 8) return -1;
        return 6;
    }
    if (D_002C6750 > 0) printf("DiskReady ended\n");
    r = *(int *)((unsigned int)D_002C81C0 | 0x20000000);
    func_00234A40(D_002C6770);
    return r;
}
