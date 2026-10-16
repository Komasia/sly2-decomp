// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
/* WIP (Claude agent): 221/264 (first draft, 2.9-991111). Structure: field setter is an inline used twice (2nd copy has xA0==1 constant-folded: no __muldi3), flag at sp+0x100 is an int, buf[0x100]; tail = range check + sceSnprintf/_sceMpegError + CscStoreRefImage/func_0024B9F0 with p1->x10 doubled. Left: target keeps &mp->x10 in s7 / pB,pC spilled to sp+0x104/0x108 (ours folds to 0x10(s3)); p2 in fp; x9C&1 and-order. */
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
        if (v >= 0) {
            *pA = v;
        } else if (d->x98 < 0) {
            *pA = v;
        } else {
            int r = d->xA0;
            int odd = r & 1;
            int s = odd & (d->x9C & 1) & (d->x90 & 1);
            *pA = d->x98 + ((int)((d->x90 * r) >> 1) + s);
            if (odd & d->x90)
                d->x9C++;
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
    *pC = (((long)p->x34 << 8 | (long)p->x2C) | ((long)p->x40 << 5 | (long)p->x3C << 6))
        | ((long)p->x38 << 7 | (long)p->x30 << 3);
    d->xA0 = 1;
    d->x98 = *pA;
}

void _dispRefImageField(D *d, P *p1, P *p2)
{
    char buf[0x100];
    long flag;
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
    mp = d->mp;
    setField(d, top, &mp->x10, &mp->x18, &mp->x20);
    mp = d->mp;
    setField(d, bot, &mp->x28, &mp->x30, &mp->x38);
    mp->x20 |= flag;
    mp->x38 |= flag;
    d->xE0 = top->x5C;
    d->xE4 = top->x60;
    d->xC8[0] = top->x44[0];
    d->xC8[1] = bot->x44[1];
    d->xC8[3] = top->x44[3];
    d->xC8[4] = bot->x44[4];
    if (d->xF4) {
        if (d->xF0 < p1->x4)
            ok = 0;
        else
            ok = !(d->xF4 < p1->x8);
    } else {
        ok = !(d->xF8 < p1->xC * p1->x10);
    }
    if (!ok) {
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
