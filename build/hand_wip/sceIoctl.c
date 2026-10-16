// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
/* WIP (Claude agent): 48/226. Structure, switch tree, inline 0x400 struct copy, tail all right. Left: target keeps constant 1 in $s5 from the prologue (used only by the `case 1` beql) and schedules i=0 before the table load in case 1 (bne delay then takes li 0x20). Tried loop forms, -fno-gcse/-fno-strict-aliasing, `one` var. */
struct iob { int fd, flags, x8, xC; };
struct SemaParam {
    int currentCount;
    int maxCount;
    int initCount;
    int numWaitThreads;
    unsigned int attr;
    unsigned int option;
};
typedef struct { char b[0x400]; } IoctlData;
typedef struct { int sema; int *res; int rsize; int fd; int req; IoctlData data; int x414; int x418; int size; } IoctlArg;
typedef struct { char b[0x440]; } FsStat;
extern int D_002C4A7C;
extern int D_002C4A78;
extern int D_002C4A8C;
extern int D_002C49F8[32];
extern void *D_0044A648;
extern IoctlArg D_0044A680;
extern FsStat D_0044B310[];
extern char D_0044BD80[];
extern int D_0044B2C0[];
extern char D_002AAB28[];
struct iob *func_002376D0(int);
int func_00237B50(int);
void func_00237B80(void);
void func_00237BD8(void);
void func_0023B170(void *, int);
int func_00234A20(struct SemaParam *);
int func_00234A30(int);
int func_00234A40(int);
int func_00234A60(int);
int func_002375E0(void *, int, int, void *, int, void *, int, void *, void *, int);

int sceIoctl(int fd, int req, void *data)
{
    struct SemaParam sp;
    int res;
    struct iob *io;
    IoctlArg *arg;
    int sema, r, i;

    arg = &D_0044A680;
    io = func_002376D0(fd);
    func_00237B50(5);
    D_0044A648 = data;
    if (D_002C4A7C == 0)
        func_00237BD8();
    if (io == 0 || io->flags == 0) {
        func_00237B80();
        return -9;
    }
    arg->x414 = 0;
    arg->x418 = 0;
    switch (req) {
    case 1:
        func_00234A60(D_002C4A8C);
        for (i = 0; i < 32; i++) {
            if (D_002C49F8[i] != -1)
                break;
        }
        if (i == 32)
            *(int *)D_0044A648 = 0;
        else
            *(int *)D_0044A648 = 1;
        func_00234A40(D_002C4A8C);
        func_00237B80();
        return 0;
    case 2:
        *(int *)data = *(int *)((unsigned int)&D_0044B310[D_002C4A78] | 0x20000000);
        func_00237B80();
        return 0;
    case 3:
        *(long *)data = *(long *)((unsigned int)&D_0044B310[D_002C4A78] | 0x20000000);
        func_00237B80();
        return 0;
    }
    arg->fd = io->fd;
    arg->req = req;
    if (data == 0) {
        arg->size = 0;
    } else {
        arg->size = 0x400;
        arg->data = *(IoctlData *)data;
    }
    sp.maxCount = 1;
    sp.option = (unsigned int)D_002AAB28;
    sp.initCount = 0;
    sema = func_00234A20(&sp);
    arg->res = &res;
    arg->rsize = 4;
    arg->sema = sema;
    func_0023B170(&D_0044A680, 0x420);
    if (func_002375E0(D_0044BD80, 5, 0, &D_0044A680, 0x420, D_0044B2C0, 4, 0, 0, 0) < 0) {
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
    func_00234A60(sema);
    func_00234A30(sema);
    return res;
}
