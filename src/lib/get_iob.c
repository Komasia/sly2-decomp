// SLY2_CC: tools/compilers/bundle/ee-gcc2.95.3-114
// SLY2_CFLAGS: -O2 -G0 
// SLY2_ASM: gnu-reorder-db
// SLY2_SAVES: sd
/* get_iob (fileio): the iob slot of file descriptor `fd`, or 0 if it is out of range. */
struct iob { int fd, flags, x8, xC; };     /* flags 0 = free */
extern int D_002C4A88;              /* iob table semaphore */
extern struct iob D_0044BB80[];     /* 32 open-file slots */
void _sceFsIobSemaMK(void);
int WaitSema(int);
int SignalSema(int);
struct iob *get_iob(unsigned int fd)
{
    struct iob *io;
    _sceFsIobSemaMK();
    WaitSema(D_002C4A88);
    if (fd < 32) {
        io = &D_0044BB80[fd];
        SignalSema(D_002C4A88);
        return io;
    }
    SignalSema(D_002C4A88);
    return 0;
}
