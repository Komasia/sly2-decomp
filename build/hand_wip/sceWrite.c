// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
/* WIP (Claude agent): 36/176. Logic/layout right. Left: (1) reg alloc - target nowait=s4, sema=s5, size=s6, flags=s7 (ours s7/s4/s5/s6); (2) head-size calc: target computes (buf>>4<<4) - (buf-16), gcc 2.9 folds to +16-buf. */
struct iob { int fd, flags, x8, xC; };
struct SemaParam {
    int currentCount;
    int maxCount;
    int initCount;
    int numWaitThreads;
    unsigned int attr;
    unsigned int option;
};
typedef struct { int sema; int *res; int rsize; int fd; void *buf; int size; int nhead; char head[16]; int idx; } WriteArg;
extern int D_002C4A7C;
extern int D_002C4A8C;
extern int D_002C49F8[32];
extern WriteArg D_0044A680;
extern struct iob D_0044BB80[];
extern char D_0044BD80[];
extern int D_0044B2C0[];
extern char D_002AAB10[];
struct iob *func_002376D0(int);
int func_00237B50(int);
void func_00237B80(void);
void func_0023B170(void *, int);
int func_00234A20(struct SemaParam *);
int func_00234A30(int);
int func_00234A40(int);
int func_00234A60(int);
int func_002375E0(void *, int, int, void *, int, void *, int, void *, void *, int);
int sceWrite(int fd, const void *buf, int size)
{
    struct SemaParam sp;
    int res;
    struct iob *io;
    WriteArg *arg;
    int sema, r, flags, nowait, i, n;

    arg = &D_0044A680;
    io = func_002376D0(fd);
    func_00237B50(3);
    if (D_002C4A7C == 0 || io == 0 || (flags = io->flags) == 0) {
        func_00237B80();
        return -9;
    }
    arg->fd = io->fd;
    arg->idx = io - D_0044BB80;
    sp.maxCount = 1;
    sp.option = (unsigned int)D_002AAB10;
    arg->size = size;
    arg->buf = (void *)buf;
    sp.initCount = 0;
    sema = func_00234A20(&sp);
    arg->res = &res;
    arg->rsize = 4;
    D_0044A680.sema = sema;
    if (flags & 0x8000) {
        func_00234A60(D_002C4A8C);
        nowait = flags & 0x8000;
        for (i = 0; i < 32; i++) {
            if (D_002C49F8[i] == -1) {
                D_002C49F8[i] = arg->sema;
                arg->sema = -arg->sema;
                break;
            }
        }
        func_00234A40(D_002C4A8C);
    } else {
        nowait = 0;
    }
    if (((unsigned int)buf & 0xF) == 0)
        n = 0;
    else
        n = ((unsigned int)buf >> 4 << 4) - ((unsigned int)buf - 16);
    if (size < n)
        n = size;
    if (!(flags & 0x20000000))
        func_0023B170((void *)buf, size);
    buf = (void *)((unsigned int)buf | 0x20000000);
    arg->nhead = n;
    for (i = 0; i < n; i++)
        arg->head[i] = ((const char *)buf)[i];
    if (func_002375E0(D_0044BD80, 3, 0, &D_0044A680, 0x30, D_0044B2C0, 4, 0, 0, nowait) < 0) {
        func_00234A30(sema);
        func_00237B80();
        return -11;
    }
    r = *(volatile int *)((unsigned int)D_0044B2C0 | 0x20000000);
    func_00237B80();
    if (r == 0) {
        func_00234A30(sema);
        return -11;
    }
    if (nowait) {
        func_00234A30(sema);
        return 0;
    }
    func_00234A60(sema);
    func_00234A30(sema);
    return res;
}
