// near-miss 12/30: only register allocation (ret in t1, type in v1 in target)
// SLY2_CC: tools/compilers/bundle/ee-gcc2.95.3-114
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
// SLY2_SAVES: sd
typedef struct { int type; } sceMpegCbData;
typedef int (*sceMpegCallback)(void *mp, sceMpegCbData *cbd, void *data);
typedef struct { sceMpegCallback func; void *data; void *gp; } CB;
typedef struct { char p0[0x40]; CB *cb; } sceMpeg;
static inline void *SetGp(void *gp)
{
    void *old;
    __asm__ volatile("move %0, $28\n\tmove $28, %1" : "=&r"(old) : "r"(gp) : "memory");
    return old;
}
int _sceMpegDispatchMpegCallback(sceMpeg *mp, sceMpegCbData *cbd) {

    int ret = 0; CB *t; sceMpegCallback f;
    if (mp && (t = mp->cb) && (f = (t + cbd->type)[1].func)) {
        void *old = SetGp(((void**)(t + cbd->type))[5]);
        ret = f(mp, cbd, (t + cbd->type)[1].data);
        SetGp(old);
    }
    return ret;
}
