// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
/* libkernel fileio sceIoctl (Claude agent). Keys: `volatile` sema table D_002C49F8 (case-1 loop); the request
   dispatch is written as the switch's own decision tree (==2, <3, ==1, ==3) with the case-1 constant in a local `one`
   set at entry - that is what keeps 1 in $s5 from the prologue; arg->sema is stored before res/rsize (gcc rotates it
   into the jal delay slot). */
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
extern volatile int D_002C49F8[32];
extern void *D_0044A648;
extern IoctlArg D_0044A680;
extern FsStat D_0044B310[];
extern char D_0044BD80[];
extern int D_0044B2C0[];
extern char D_002AAB28[];
struct iob *get_iob(int);
int _sceFsWaitS(int);
void func_00237B80(void);
void sceFsInit(void);
void sceSifWriteBackDCache(void *, int);
int CreateSema(struct SemaParam *);
int DeleteSema(int);
int SignalSema(int);
int WaitSema(int);
int sceFsSifCallRpc(void *, int, int, void *, int, void *, int, void *, void *, int);

int sceIoctl(int fd, int req, void *data)
{
    struct SemaParam sp;
    int res;
    struct iob *io;
    IoctlArg *arg;
    int sema, r, i;
    int one = 1;    /* case value held in a register from the prologue, as in the target */

    arg = &D_0044A680;
    io = get_iob(fd);
    _sceFsWaitS(5);
    D_0044A648 = data;
    if (D_002C4A7C == 0)
        sceFsInit();
    if (io == 0 || io->flags == 0) {
        func_00237B80();
        return -9;
    }
    arg->x414 = 0;
    arg->x418 = 0;
    if (req == 2) goto c2;
    if (req < 3) { if (req == one) goto c1; goto dflt; }
    if (req == 3) goto c3;
    goto dflt;
    c1: {
        WaitSema(D_002C4A8C);
        for (i = 0; i < 32; i++) {
            if (D_002C49F8[i] != -1)
                break;
        }
        if (i == 32)
            *(int *)D_0044A648 = 0;
        else
            *(int *)D_0044A648 = 1;
        SignalSema(D_002C4A8C);
        func_00237B80();
        return 0;
    }
    c2: {
        *(int *)data = *(int *)((unsigned int)&D_0044B310[D_002C4A78] | 0x20000000);
        func_00237B80();
        return 0;
    }
    c3: {
        *(long *)data = *(long *)((unsigned int)&D_0044B310[D_002C4A78] | 0x20000000);
        func_00237B80();
        return 0;
    }
    dflt:
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
    sema = CreateSema(&sp);
    arg->sema = sema;
    arg->res = &res;
    arg->rsize = 4;
    sceSifWriteBackDCache(&D_0044A680, 0x420);
    if (sceFsSifCallRpc(D_0044BD80, 5, 0, &D_0044A680, 0x420, D_0044B2C0, 4, 0, 0, 0) < 0) {
        DeleteSema(sema);
        func_00237B80();
        return -11;
    }
    r = *(volatile int *)((unsigned int)D_0044B2C0 | 0x20000000);
    func_00237B80();
    if (r == 0) {
        DeleteSema(sema);
        return -11;
    }
    WaitSema(sema);
    DeleteSema(sema);
    return res;
}
