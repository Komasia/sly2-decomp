// WIP draft (Claude agent): 239/248, control flow + layout reconstructed (BS @sp, HEADER/PES @sp+0x30, CBDATA @sp+0x80, spills 0xA0-0xAC); target addresses BS via a pointer (s1/a2=sp) - probably inline BS helpers; reg alloc far off.
// SLY2_CC: tools/compilers/bundle/ee-gcc2.95.3-114
// SLY2_CFLAGS: -O2 -G0 -fstrict-aliasing
// SLY2_ASM: gnu-reorder-db
// SLY2_SAVES: sd
typedef struct {
    unsigned long buf, pos;
    unsigned char *base;
    unsigned char *cur;
    int bits;
    unsigned char *start, *end;
    int size;
} BS;
typedef struct { unsigned int extension, low, high, hasSystemHeader; } HEADER;
typedef struct {
    unsigned long id;
    unsigned long x8;
    unsigned long pts;
    unsigned long dts;
    int x20;
    int len;
    int x28;
} PES;
typedef struct { HEADER hdr; int pad[2]; PES pes; } PSS;
typedef struct {
    int type;
    unsigned char *data;
    unsigned char *data2;
    int len;
    unsigned long pts;
    unsigned long dts;
} CBDATA;
typedef int (*CBFUNC)(void *mp, CBDATA *cb, void *data);
typedef struct {
    unsigned long id;
    unsigned long mask;
    CBFUNC func;
    void *data;
    void *gp;
    int pad;
} CBENT;
typedef struct { char p0[0x60]; CBENT *tbl; int n; } MI;
typedef struct { char p0[0x40]; MI *mi; } MPEG;
extern int _pack_header(BS *p, HEADER *out);
extern int _PES_packet(MI *mi, BS *p, PES *pes);

static inline void *SetGP(void *gp)
{
    void *old;
    __asm__ volatile("move %0, $gp\n\tmove $gp, %1" : "=&r"(old) : "r"(gp) : "memory");
    return old;
}

int sceMpegDemuxPssRing(MPEG *mp, unsigned char *addr, int size, unsigned char *buftop, int bufsize)
{
    BS bs;
    BS *bp = &bs;
    PSS pss;
    CBDATA cb;
    void *cbdata;
    CBENT *tbl;
    int result;
    void *cbgp;
    MI *mi = mp->mi;
    CBFUNC func = 0;
    int limit = size << 3;
    int cont = 1;
    int i, n;
    void *old;

    tbl = mi->tbl;
    bp->end = buftop + bufsize;
    bp->size = bufsize;
    bp->cur = addr;
    bp->base = addr;
    cbdata = 0;
    bp->pos = 0;
    bp->start = buftop;
    result = 0;
    bp->buf = 0;
    cbgp = 0;
    bp->bits = 0;
    do {
        unsigned char *cur = bp->cur;
        int bits = bp->bits;
        bp->buf |= (unsigned long)*cur << (56 - bits);
        bp->cur = ++cur;
        if (cur >= bp->end) bp->cur = bp->start;
        bp->bits = bits + 8;
    } while (bp->bits < 57);
    bp->pos = 0;

    n = mi->n;
    for (i = 0; i < n; i++) {
        CBENT *e = &tbl[i];
        if (e->id == 0xBDFF000000) {
            cbgp = e->gp;
            func = e->func;
            cbdata = e->data;
        }
        if (func) break;
    }
    if ((int)(bp->buf >> 32) == 0x1BA)
        _pack_header(bp, &pss.hdr);
    for (;;) {
        while ((bp->buf >> 40) == 1 && (int)(bp->buf >> 32) != 0x1BA && (int)(bp->buf >> 32) != 0x1B9
               && (int)bp->pos < limit && cont) {
            _PES_packet(mi, bp, &pss.pes);
            if (limit < (int)bp->pos)
                continue;
            n = mi->n;
            for (i = 0; i < n; i++) {
                CBENT *e = &mi->tbl[i];
                if (e->id == (pss.pes.id & e->mask)) {
                    unsigned char *p;
                    cb.type = 6;
                    p = bp->base + (pss.pes.x28 >> 3);
                    if (p >= bp->end) p -= bp->size;
                    cb.data = p;
                    p = bp->base + (pss.pes.x20 >> 3);
                    if (p >= bp->end) p -= bp->size;
                    cb.pts = pss.pes.pts;
                    cb.data2 = p;
                    cb.len = pss.pes.len;
                    cb.dts = pss.pes.dts;
                    old = SetGP(e->gp);
                    cont = e->func(mp, &cb, e->data);
                    SetGP(old);
                    break;
                }
            }
            if (i == mi->n && func) {
                unsigned char *p;
                cb.type = 6;
                p = bp->base + (pss.pes.x28 >> 3);
                if (p >= bp->end) p -= bp->size;
                cb.data = p;
                p = bp->base + (pss.pes.x20 >> 3);
                if (p >= bp->end) p -= bp->size;
                cb.pts = pss.pes.pts;
                cb.data2 = p;
                cb.len = pss.pes.len;
                cb.dts = pss.pes.dts;
                old = SetGP(cbgp);
                cont = func(mp, &cb, cbdata);
                SetGP(old);
            }
            if (cont)
                result = (int)(bp->pos >> 3);
        }
        if (limit < (int)bp->pos)
            break;
        if ((int)(bp->buf >> 32) != 0x1BA)
            break;
        _pack_header(bp, &pss.hdr);
    }
    return result;
}
