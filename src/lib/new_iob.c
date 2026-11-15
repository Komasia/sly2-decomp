// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
__asm__(".macro sq r, m\n\tsd \\r, \\m\n\t.endm\n\t.macro lq r, m\n\tld \\r, \\m\n\t.endm");
/* new_iob (fileio): claim the first free iob slot (0 if all 32 are in use). */
struct iob { int fd, flags, x8, xC; };     /* flags 0 = free */
extern int D_002C4A88;              /* iob table semaphore */
extern struct iob D_0044BB80[];     /* 32 open-file slots */
void _sceFsIobSemaMK(void);
int WaitSema(int);
int SignalSema(int);
struct iob *new_iob(void)
{
    struct iob *io;
    _sceFsIobSemaMK();
    WaitSema(D_002C4A88);
    for (io = D_0044BB80; io < D_0044BB80 + 32; io++) {
        if (io->flags == 0) {
            io->flags = 0x10000000;     /* in use */
            SignalSema(D_002C4A88);
            return io;
        }
    }
    SignalSema(D_002C4A88);
    return 0;
}
