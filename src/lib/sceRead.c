// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
/* sceRead (fileio): read `size` bytes from `fd` into `buf` (a nowait file, flag 0x8000, returns at once);
   returns the byte count or a negative errno.
   codegen keys: `nowait` assigned in a nested do{do{}while(0);}while(0) after
   `i = 0` (global-alloc priority); and the dead `r = (int)<table>` first statement of each arm: it computes the arm's
   `lui` itself, so gcse PRE no longer appends it AFTER `i = 0` / `nowait = 0` (the target has lui first in both arms). */
struct iob { int fd, flags, x8, xC; };
struct SemaParam {
    int currentCount;
    int maxCount;
    int initCount;
    int numWaitThreads;
    unsigned int attr;
    unsigned int option;
};
typedef struct { int sema; int *res; int rsize; int fd; void *buf; int size; int x18; int idx; } ReadArg;
extern int D_002C4A7C;    /* fileio initialised */
extern int D_002C4A8C;    /* nowait-request table semaphore */
extern int D_002C49F8[32];    /* per-iob semaphore of a pending nowait request (-1 = none) */
extern ReadArg D_0044A680;    /* RPC argument block */
extern struct iob D_0044BB80[];    /* open-file (iob) table */
extern char D_0044BD80[];    /* fileio RPC client */
extern int D_0044B2C0[];    /* RPC reply (read uncached) */
extern char D_002AAAF8[];    /* "SceStdioReadSema" */
struct iob *get_iob(int);
int _sceFsWaitS(int);
void func_00237B80(void);
void sceSifWriteBackDCache(void *, int);
int CreateSema(struct SemaParam *);
int DeleteSema(int);
int SignalSema(int);
int WaitSema(int);
int sceFsSifCallRpc(void *, int, int, void *, int, void *, int, void *, void *, int);
int sceRead(int fd, void *buf, int size)
{
    struct SemaParam sp;
    int res;
    struct iob *io;
    ReadArg *arg;
    int sema, r, flags, nowait, i;

    arg = &D_0044A680;
    io = get_iob(fd);
    _sceFsWaitS(2);
    if (D_002C4A7C == 0 || io == 0 || (flags = io->flags) == 0) {
        func_00237B80();
        return -9;
    }
    arg->fd = io->fd;
    arg->idx = io - D_0044BB80;
    sp.maxCount = 1;
    sp.option = (unsigned int)D_002AAAF8;
    arg->buf = buf;
    arg->size = size;
    sp.initCount = 0;
    sema = CreateSema(&sp);
    arg->res = &res;
    arg->rsize = 4;
    D_0044A680.sema = sema;
    if (flags & 0x8000) {
        WaitSema(D_002C4A8C);
        r = (int)D_002C49F8;
        i = 0;
        do { do { nowait = flags & 0x8000; } while (0); } while (0);
        for (; i < 32; i++) {
            if (D_002C49F8[i] == -1) {
                D_002C49F8[i] = arg->sema;
                arg->sema = -arg->sema;
                break;
            }
        }
        SignalSema(D_002C4A8C);
    } else {
        r = (int)D_0044B2C0;
        nowait = 0;
    }
    if (!(flags & 0x20000000))
        sceSifWriteBackDCache(buf, size);
    sceSifWriteBackDCache(arg, 0x20);
    if (sceFsSifCallRpc(D_0044BD80, 2, 0, &D_0044A680, 0x20, D_0044B2C0, 4, 0, 0, nowait) < 0) {
        DeleteSema(sema);
        func_00237B80();
        return -11;
    }
    r = *(int *)((unsigned int)D_0044B2C0 | 0x20000000);
    func_00237B80();
    if (r == 0) {
        DeleteSema(sema);
        return -11;
    }
    if (nowait) {
        DeleteSema(sema);
        return 0;
    }
    WaitSema(sema);
    DeleteSema(sema);
    return res;
}
