// SLY2_CC: tools/compilers/bundle/ee-gcc2.95.3-136
// SLY2_CFLAGS: -O2 -G0 -ffast-math -mvu0-use-vf0-vf31
typedef struct { float x, y, z, w; } V4;
typedef struct { V4 r[3]; } M3 __attribute__((aligned(16)));
typedef struct { char pad[0x50]; int x50; char pad2[0xC]; M3 m; } S;
M3 func_0022FD38(int, int, int); void func_002313F0(S *);
void func_00231300(S *p, int x)
{
    M3 *m;
    M3 t = func_0022FD38(0, p->x50, x);
    m = &p->m;
    *m = t;
    m->r[2].w = 0;
    m->r[1].w = 0;
    m->r[0].w = 0;
    func_002313F0(p);
}
