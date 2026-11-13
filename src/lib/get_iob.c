// SLY2_CC: tools/compilers/bundle/ee-gcc2.95.3-114
// SLY2_CFLAGS: -O2 -G0 
// SLY2_ASM: gnu-reorder-db
// SLY2_SAVES: sd
struct iob { int x0, x4, x8, xC; };
extern int D_002C4A88;
extern struct iob D_0044BB80[];
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
