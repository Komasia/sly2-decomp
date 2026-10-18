// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
typedef struct {
    int addr;
    int frac;
    int n1;
    int n2;
    int step;
    int p1;
    int p2;
} MCB;
typedef struct {
    int base;
    int x4;
    int top[4];
    int bot[4];
    void (*fnA[4])(MCB *);
    void (*fnB[4])(MCB *);
    MCB a[4];
    MCB b[4];
    int x128;
    int n;
    int flag;
    int pad134;
    int enable;
    int flag2;
} REFS;
typedef struct {
    char pad0[0x5A0];
    REFS refs[2];
    int cur;
    char pad824[0x830 - 0x824];
    int x830;
    char pad834[0x87C - 0x834];
    int x87C;
} D;
typedef struct { int addr; int x4; int x8; int xC; int w; } PIC;
extern void (*D_002C8478[])(MCB *);
extern void (*D_002C8498[])(MCB *);
void _getRef0(D *d_arg, PIC *p_arg, int a2_arg, int a3, int t0_arg, int h_arg, int t2, int t3_arg, int mx_arg, int my_arg, int fl_arg, int sel)
{
    register PIC *p asm("$5") = p_arg;
    register D *d asm("$15") = d_arg;
    register int a2 asm("$18") = a2_arg;
    register int t0 asm("$16") = t0_arg;
    register int t3 asm("$17") = t3_arg;
    register int h asm("$14") = h_arg;
    int mx = mx_arg;
    int my = my_arg;
    int fl = fl_arg;

    int ia, xh, yh;
    int pa, idx, fx, fy, top, bot, base, hx, hy, hh, w, v, cx, cy, ox, oy, o;
    register MCB *ra asm("$12");
    register MCB *rb asm("$13");
    register int k asm("$25");
    register int c asm("$19");
    register int x asm("$10");
    register int y asm("$11");
    register int mbx asm("$22");
    register int mby asm("$23");
    c = d->cur;
    k = d->refs[c].n;
    o = d->x830;
    x = (mx >> 1) + t2;
    ra = &d->refs[c].a[k];
    rb = &d->refs[c].b[k];
    {
        register int yHead asm("$2");
        register int yBase asm("$3");
        if (fl) {
            yHead = my >> 1;
            yBase = t0 + a2;
            yHead <<= 1;
        } else {
            yHead = my >> 1;
            yBase = t0 + a2;
        }
        yHead += t3;
        y = yHead + yBase;
    }
    w = p->w;
    pa = p->addr;
    mbx = x >> 4;
    mby = y >> 4;
    idx = mbx * w + mby;
    ra->frac = x - (mbx << 4);
    top = pa + idx * 0x180;
    bot = pa + (idx + w) * 0x180;
    { int *pt = &d->refs[c].top[k]; pt[0] = top; pt[4] = bot; }
    ra->addr = o + ((a3 + t0) << 5);
    fy = y - (mby << 4);
    yh = my & 1;
    xh = mx & 1;
    if (yh) {
        if (fy + (h << fl) < 16)
            goto small_ra;
        {
        int v1 = (16 >> fl) - (fy >> fl) - 1;
        ra->n1 = v1;
        ra->n2 = h - v1;
        }
    } else {
        if (fy + (h << fl) < 17)
            goto small_ra;
        {
        int v1 = (16 >> fl) - (fy >> fl);
        ra->n1 = v1;
        ra->n2 = h - v1;
        }
    }
    goto done_ra;
small_ra:
    ra->n1 = h;
    ra->n2 = 0;
done_ra:
    if (d->x87C == 0) {
        base = d->refs[d->cur].base + k * 0x600;
        ra->p1 = base + (fy << 4);
        { int e3 = (fy << 4) + 0x300; ra->p2 = base + e3; }
    } else {
        base = top;
        ra->p2 = bot + (fy << 4);
        ra->p1 = top + (fy << 4);
    }
    ia = (sel << 2) | (xh << 1) | yh;
    ra->step = 16 << fl;
    hx = mx / 2;
    hy = my / 2;
    hh = h >> 1;
    cx = (hx >> 1) + (t2 >> 1);
    if (fl)
        cy = ((hy >> 1) << 1) + (t3 >> 1) + ((t0 >> 1) + a2);
    else
        cy = (hy >> 1) + (t3 >> 1) + ((t0 >> 1) + a2);
    ox = cx >> 3;
    oy = cy >> 3;
    rb->frac = cx - (ox << 3);
    rb->addr = o + ((a3 + (t0 >> 1)) << 4) + 0x200;
    fy = cy - (oy << 3);
    xh = hx & 1;
    yh = hy & 1;
    if (yh) {
        if (fy + (hh << fl) < 8)
            goto small_rb;
        {
        int v1 = (8 >> fl) - (fy >> fl) - 1;
        rb->n1 = v1;
        rb->n2 = hh - v1;
        }
    } else {
        if (fy + (hh << fl) < 9)
            goto small_rb;
        {
        int v1 = (8 >> fl) - (fy >> fl);
        rb->n1 = v1;
        rb->n2 = hh - v1;
        }
    }
    goto done_rb;
small_rb:
    rb->n1 = hh;
    rb->n2 = 0;
done_rb:
    v = (((ox - mbx) << 1) + (oy - mby)) * 0x180;
    if (d->x87C == 0) {
        int e4, e1, bv;
        bv = base + v;
        e4 = (fy << 3) + 0x400;
        e1 = (fy << 3) + 0x100;
        rb->p1 = bv + e1;
        rb->p2 = bv + e4;
    } else {
        int e1, e2;
        e1 = (fy << 3) + 0x100;
        if ((unsigned int)(v + e1) < 0x301)
            rb->p1 = (top + v) + e1;
        else {
            rb->p1 = ((bot + v) + e1) - 0x300;
        }
        e2 = (fy << 3) + 0x100;
        rb->p2 = (bot + v) + e2;
    }
    rb->step = 8 << fl;
    {
        int c2 = d->cur;
        d->refs[c2].fnA[k] = D_002C8478[ia];
        d->refs[c2].n++;
        d->refs[c2].fnB[k] = D_002C8498[(sel << 2) | (xh << 1) | yh];
    }
}
