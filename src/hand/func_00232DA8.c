// SLY2_CC: tools/compilers/bundle/ee-gcc2.95.3-136
// SLY2_CFLAGS: -O2 -G0
extern int gStreamingInited;
extern int gSSReadDone;
extern int D_00448400[];
int func_00241E88(void);
void func_00235078(void *, void *);
void func_00231C48(void);

int snd_StreamSafeCdSync(int mode)
{
    char *pe;
    if (!gStreamingInited)
        return func_00241E88();
    pe = (char *)D_00448400 + 0x3F;
    func_00235078(D_00448400, pe);
    gSSReadDone = (D_00448400[0] == 0);
    if (gSSReadDone == 1)
        return 0;
    if (mode == 1)
        return 1;
    while (!gSSReadDone) {
        func_00231C48();
        func_00235078(D_00448400, pe);
        gSSReadDone = (D_00448400[0] == 0);
    }
    return 0;
}
