/* WIP lilly4 (T1594): aligned 24 with ONE register pin (w in $7 = a3, where the target keeps it). Same source as lilly3 otherwise.
   Left: (1) k*4 is reloaded once (+1 insn; target keeps it in t0: in its sched1 order k*4 + c*0x140 comes before idx*0x180), mbx*w in a0 (target v1), c*0x140 mult vs mult1;
   (2) chroma v block: 0x180 / d->x87C in a1 / a0 (target a0 / a1), sum operand order. */
/* WIP (Claude agent) v6 (2026-10-17): aligned 154 (v5 163): v5 + the four n1 temporaries as block-scoped 'int v1' inside braces. Separate chroma fy: 290 insns but aligned 177; separate chroma xh/yh: 153 but more opcode diffs. */
/* WIP (Claude agent) v3 (2026-10-17): 281/290, aligned 191 (v2: 211). Instruction count and 0xB0 frame now right:
   xh/yh = mx&1/my&1 (then hx&1/hy&1) locals computed before each n1/n2 if (target computes both andi together and
   reuses them for the fnA/fnB index); tail reloads c = d->cur once. Left: register allocation (target d=t7, c=s3,
   k=t9, x=t2, h=t6; s0/s1/s2 = t0/t3/a2 args). Variant without the c reload: 291 insns, aligned 182.
   v2 notes: */
/* WIP (Claude agent) v2: 253/290 positional (288 vs 290 insns, normalized-reg ratio 0.67 vs 0.64 for v1). Changes vs _getRef0.c:
   fnA index 'ia' computed right after luma (target spills sel<<2 to sp+0x14 there), n1=h/n2=0 tails shared via goto.
   Left: frame 0xA0 vs 0xB0 (target spills bx to sp+4, k*4 to sp+0x10), register allocation throughout. */
// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
/* WIP (Claude agent): 278/290 (first full draft; instruction count right). 12 args (8 regs + 4 stack). Builds luma (refs[cur].a[k]) and chroma (b[k]) MC blocks, fnA/fnB from tables D_002C8478/D_002C8498, refs[cur].n++. Left: register allocation/spills (target frame 0xB0 with k*4 and sel<<2 spilled at sp+0x10/0x14; p kept in a1, mx in fp). */
typedef struct {
    int addr;   /* 0x00 */
    int frac;   /* 0x04 */
    int n1;     /* 0x08 */
    int n2;     /* 0x0C */
    int step;   /* 0x10 */
    int p1;     /* 0x14 */
    int p2;     /* 0x18 */
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
    int cur;        /* 0x820 */
    char pad824[0x830 - 0x824];
    int x830;
    char pad834[0x87C - 0x834];
    int x87C;
} D;
typedef struct { int addr; int x4; int x8; int xC; int w; } PIC;
extern void (*D_002C8478[])(MCB *);
extern void (*D_002C8498[])(MCB *);

void _getRef0(D *d, PIC *p, int a2, int a3, int t0, int h, int t2, int t3, int mx, int my, int fl, int sel)
{
    int ia, xh, yh, t0h, bv;
    int pa, x, y, mbx, mby, idx, fx, fy, top, bot, base, hx, hy, hh, v, ox, oy, k, o, c;
    MCB *ra, *rb;
    register int w asm("$7");  /* pin: target keeps w in a3; unpinned, local-alloc gives a3 to idx * 0x180 instead (see notes/245000.md) */

    c = d->cur;
    o = d->x830;
    k = d->refs[c].n;
    x = (mx >> 1) + t2;
    ra = &d->refs[c].a[k];
    rb = &d->refs[c].b[k];
    if (fl)
        y = ((my >> 1) << 1) + t0 + (t3 + a2);
    else
        y = (my >> 1) + t0 + (t3 + a2);
    mby = y >> 4;
    pa = p->addr;
    mbx = x >> 4;
    w = p->w;
    fy = y - (mby << 4);
    idx = mbx * w + mby;
    top = pa + idx * 0x180;
    ra->frac = x - (mbx << 4);
    bot = (idx + w) * 0x180 + pa;
    ra->addr = ((a3 + t0) << 5) + o;
    d->refs[c].top[k] = top;
    yh = my & 1;
    d->refs[c].bot[k] = bot;
    xh = mx & 1;
    if (yh) {
        if (fy + (h << fl) >= 16) {
            int v1 = (16 >> fl) - (fy >> fl) - 1;
            ra->n1 = v1;
            ra->n2 = h - v1;
        } else {
            ra->n1 = h;
            ra->n2 = 0;
        }
    } else {
        if (fy + (h << fl) >= 17) {
            int v1 = (16 >> fl) - (fy >> fl);
            ra->n1 = v1;
            ra->n2 = h - v1;
        } else {
            ra->n1 = h;
            ra->n2 = 0;
        }
    }
    if (d->x87C == 0) {
        base = d->refs[d->cur].base + k * 0x600;
        ra->p1 = base + (fy << 4);
        { int e3 = (fy << 4) + 0x300; ra->p2 = base + e3; }
    } else {
        base = top;
        ra->p1 = top + (fy << 4);
        ra->p2 = bot + (fy << 4);
    }
    ra->step = 16 << fl;
    hx = mx / 2;
    ia = (sel << 2) | (xh << 1) | yh;
    x = (hx >> 1) + (t2 >> 1);
    t0h = t0 >> 1;

    hh = h >> 1;
    hy = my / 2;
    if (fl)
        y = ((hy >> 1) << 1) + t0h + ((t3 >> 1) + a2);
    else
        y = (hy >> 1) + t0h + ((t3 >> 1) + a2);
    xh = hx & 1;
    oy = y >> 3;
    ox = x >> 3;
    yh = hy & 1;
    rb->frac = x - ox * 8;
    rb->addr = o + 0x200 + ((a3 + t0h) << 4);
    fy = y - (oy << 3);
    if (yh) {
        if (fy + (hh << fl) >= 8) {
            int v1 = (8 >> fl) - (fy >> fl) - 1;
            rb->n1 = v1;
            rb->n2 = hh - v1;
        } else {
            rb->n1 = hh;
            rb->n2 = 0;
        }
    } else {
        if (fy + (hh << fl) >= 9) {
            int v1 = (8 >> fl) - (fy >> fl);
            rb->n1 = v1;
            rb->n2 = hh - v1;
        } else {
            rb->n1 = hh;
            rb->n2 = 0;
        }
    }
    v = (((ox - mbx) << 1) + (oy - mby)) * 0x180;
    bv = base + v;
    if (d->x87C == 0) {
        int e1, e2;
        e1 = (fy << 3) + 0x100;
        e2 = (fy << 3) + 0x400;
        rb->p1 = bv + e1;
        rb->p2 = bv + e2;
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
