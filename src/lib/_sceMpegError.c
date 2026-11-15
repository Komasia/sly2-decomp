// SLY2_CC: tools/compilers/bundle/ee-gcc2.95.3-136
// SLY2_CFLAGS: -O2 -G0
/* _sceMpegError (libmpeg): report an error to the application's sceMpegCbError callback, or print it if
   none is registered. */
typedef struct { int type; int code; } sceMpegCbDataError;
typedef struct { char pad[0xC]; int cb; } CBS;     /* callback table starts at 0x0C; [0] = error */
typedef struct { char pad[0x868]; void *mp; } DEC;
int _sceMpegDispatchMpegCallback(void *, void *);
void func_0024F8C0(int);   /* print the message (no callback) */
void _sceMpegError(DEC *d, int code)
{
    void *mp = d->mp;
    if (mp && d && ((CBS *)d)->cb) {
        sceMpegCbDataError e;
        e.code = code;
        e.type = 0;     /* sceMpegCbError */
        _sceMpegDispatchMpegCallback(mp, &e);
    } else {
        func_0024F8C0(code);
    }
}
