// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
/* v2 (Claude agent): aligned 29 (v1 92). ok = !(xF0<x4) && !(xF4<x8); error test `ok != 1`. int flag; per-call d->mp in args; `if (v<0 && x98>=0) {compute} else *pA=v`; long t/u temps for the odd/x9C/x90 bit; x90*r; pC = (x2C|x34<<8)|(x30<<3|x38<<7)|(x40<<5|x3C<<6). */
typedef struct { char p0[0x10]; long x10; long x18; long x20; long x28; long x30; long x38; } MP;
typedef struct {
    int x0; int x4; int x8; int xC; int x10; int p14; long x18; long x20;
    int x28; int x2C; int x30; int x34; int x38; int x3C; int x40;
    int x44[6]; int x5C; int x60;
} P;
typedef struct {
    char p0[0x8]; int x8;
    char pC[0x8C - 0xC]; int x8C; long x90; int x98; int x9C; long xA0;
    char pA8[0xC0 - 0xA8]; int xC0; int xC4; int xC8[6]; int xE0; int xE4;
    char pE8[0xF0 - 0xE8]; int xF0; int xF4; int xF8;
    char pFC[0x100 - 0xFC]; long x100; int x108;
    char p10C[0x128 - 0x10C]; int x128;
    char p12C[0x184 - 0x12C]; int x184;
    char p188[0x834 - 0x188]; int x834;
    char p838[0x868 - 0x838]; MP *mp;
} D;
int sceSnprintf(char *buf, unsigned int n, const char *fmt, ...);
void _sceMpegError(D *d, const char *msg);
void _sceMpegCscStoreRefImage(D *d, P *p);
void func_0024B9F0(D *d, P *p);
extern char D_002AC438[];

static inline void setField(D *d, P *p, long *pA, long *pB, long *pC)
{
    if (d->x8C) {
        long v = p->x18;
        if (v < 0 && d->x98 >= 0) {
            int r = d->xA0;
            int odd = r & 1;
            long t = d->x9C & 1;
            long u = d->x90 & 1;
            int s = odd & t & u;
            *pA = d->x98 + ((int)((d->x90 * r) >> 1) + s);
            if (odd & d->x90)
                d->x9C++;
        } else {
            *pA = v;
        }
    } else {
        *pA = p->x18;
    }
    if (d->x108 == 2 && d->x100 >= 0) {
        *pA = d->x100;
        d->x108 = 0;
        d->x100 = -1;
    }
    *pB = p->x20;
    *pC = (((long)p->x2C | (long)p->x34 << 8) | ((long)p->x30 << 3 | (long)p->x38 << 7)) | ((long)p->x40 << 5 | (long)p->x3C << 6);
    d->xA0 = 1;
    d->x98 = *pA;
}

void _dispRefImageField(D *d, P *p1, P *p2)
{
    char buf[0x100];
    int flag;
    P *top, *bot;
    MP *mp;
    int ok;

    flag = 0;
    if (d->x184 == 2) {
        flag = 0x40;
        top = p1;
        bot = p2;
    } else {
        top = p2;
        bot = p1;
    }
    setField(d, top, &d->mp->x10, &d->mp->x18, &d->mp->x20);
    setField(d, bot, &d->mp->x28, &d->mp->x30, &d->mp->x38);
    mp = d->mp;
    mp->x20 |= flag;
    mp->x38 |= flag;
    d->xE0 = top->x5C;
    d->xE4 = top->x60;
    d->xC8[0] = top->x44[0];
    d->xC8[1] = bot->x44[1];
    d->xC8[3] = top->x44[3];
    d->xC8[4] = bot->x44[4];
    if (d->xF4) {
        ok = !(d->xF0 < p1->x4) && !(d->xF4 < p1->x8);
    } else {
        ok = !(d->xF8 < p1->xC * p1->x10);
    }
    if (ok != 1) {
        sceSnprintf(buf, 0x100, D_002AC438, p1->x4, p1->x8);
        _sceMpegError(d, buf);
    }
    if (ok && p1->x28 == 1 && p2->x28 == 1) {
        p1->x10 *= 2;
        if (d->xC4)
            _sceMpegCscStoreRefImage(d, p1);
        else
            func_0024B9F0(d, p1);
        p1->x10 >>= 1;
        if (d->x8 != 2) {
            d->x8 = 2;
            d->xC0 = d->x128;
        }
        d->x834 = 1;
    }
}
