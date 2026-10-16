// (Claude agent) libmpeg _dispRefImage, full structure. 115/176. Keys: -fstrict-aliasing + 'memory' asm after the __muldi3 product (target reloads d->x98/d->mp after the libcall; mp reload is PRE on that path), xF4!=0 test first, (int)(x20>>5)&0xF. Left: target keeps *pA stores via s5 (ours folds to 0x10(s4) in first block -> block layout of the bltzl path), x90 loaded straight into a0.
// SLY2_CC: tools/compilers/bundle/ee-gcc2.95.3-114
// SLY2_CFLAGS: -O2 -G0 -fstrict-aliasing
// SLY2_ASM: gnu-reorder-db
// SLY2_SAVES: sd
typedef struct { char p0[0x10]; long x10; long x18; long x20; } MP;
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
    char p12C[0x834 - 0x12C]; int x834;
    char p838[0x868 - 0x838]; MP *mp;
} D;
extern unsigned int D_002C8398[];
int sceSnprintf(char *buf, unsigned int n, const char *fmt, ...);
void _sceMpegError(D *d, const char *msg);
void _sceMpegCscStoreRefImage(D *d, P *p);
void _cpr8(D *d);

void _dispRefImage(D *d, P *p)
{
    MP *mp = d->mp;
    long *pA = &mp->x10;
    long *pB = &mp->x18;
    long *pC = &mp->x20;
    int ok;

    if (d->x8C) {
        long v = p->x18;
        if (v >= 0) {
            *pA = v;
        } else if (d->x98 < 0) {
            *pA = v;
        } else {
            int r = d->xA0;
            long t = d->x90;
            int odd = r & 1;
            int s = odd & (d->x9C & 1) & (t & 1);
            { long m = t * r; __asm__ __volatile__("" ::: "memory"); mp->x10 = d->x98 + ((int)(m >> 1) + s); }
            if (odd & d->x90) d->x9C++;
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
    d->x98 = d->mp->x10;
    d->xA0 = D_002C8398[(int)(d->mp->x20 >> 5) & 0xF];
    d->xE0 = p->x5C;
    d->xE4 = p->x60;
    d->xC8[0] = p->x44[0];
    d->xC8[1] = p->x44[1];
    d->xC8[2] = p->x44[2];
    d->xC8[3] = p->x44[3];
    d->xC8[4] = p->x44[4];
    d->xC8[5] = p->x44[5];
    if (d->xF4)
        ok = d->xF0 >= p->x4 && d->xF4 >= p->x8;
    else
        ok = d->xF8 >= p->xC * p->x10;
    if (!ok) {
        char buf[256];
        sceSnprintf(buf, 256, "Too small buffer size for %dx%d picture\n", p->x4, p->x8);
        _sceMpegError(d, buf);
    }
    if (ok && p->x28 == 1) {
        if (d->xC4) _sceMpegCscStoreRefImage(d, p);
        else _cpr8(d);
        if (d->x8 != 2) {
            d->x8 = 2;
            d->xC0 = d->x128;
        }
        d->x834 = 1;
    }
}
