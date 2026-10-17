// WIP v3 (Claude agent, 2026-10-17): aligned 136 (v2 161). Everything after Fill() moved into static inline Run(mp, mi, BS *bs, PSS *pss, tbl, limit)
// (gives the target's s1 = sp bs pointer); bdff search loop as 'if (n > 0) do { ...; if (func) break; i++; } while (i < n);' (rotated like target, blez);
// then-block order data, func, gp. Left: target keeps pss pointer in s2 and func in fp; ours gives cb address (sp+0x80) s7 and the hoisted constant 6 fp, frame 0x160 vs 0x150.
// WIP v2 (Claude agent, 2026-10-17): ee-gcc2.9 (no SAVES), aligned 161 (v1 173). Ring-fill loop as `static inline Fill(BS *p)`
// with `*p->cur++` (as in matched src/lib/_pack_header.c) now matches exactly incl. a2 = sp pointer copy; `tbl` local reused
// in the PES callback loop (target re-reads its spill at 0xA4(sp); with mi->tbl: aligned 157 but positional worse).
// Left: s-register assignment (target bs pointer s1 = sp, pss s2, mp s7?, fp = func) - try the main loop in an inline taking BS *.
// v1 notes: 239/248, control flow + layout reconstructed (BS @sp, HEADER/PES @sp+0x30, CBDATA @sp+0x80, spills 0xA0-0xAC); target addresses BS via a pointer (s1/a2=sp) - probably inline BS helpers; reg alloc far off.
// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
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

static inline void Fill(BS *p)
{
    do {
        p->buf |= (unsigned long)*p->cur++ << (56 - p->bits);
        if (p->cur >= p->end) p->cur = p->start;
        p->bits += 8;
    } while (p->bits < 57);
    p->pos = 0;
}

static inline int Run(MPEG *mp, MI *mi, BS *bs, PSS *pss, CBENT *tbl, int limit)
{
    CBDATA cb;
    void *cbdata = 0;
    void *cbgp = 0;
    CBFUNC func = 0;
    int result = 0;
    int cont = 1;
    int i, n;
    void *old;

    n = mi->n;
    i = 0;
    if (n > 0) do {
        CBENT *e = &tbl[i];
        if (e->id == 0xBDFF000000) {
            cbdata = e->data;
            func = e->func;
            cbgp = e->gp;
        }
        if (func) break;
        i++;
    } while (i < n);
    if ((int)(bs->buf >> 32) == 0x1BA)
        _pack_header(bs, &pss->hdr);
    for (;;) {
        while ((bs->buf >> 40) == 1 && (int)(bs->buf >> 32) != 0x1BA && (int)(bs->buf >> 32) != 0x1B9
               && (int)bs->pos < limit && cont) {
            _PES_packet(mi, bs, &pss->pes);
            if (limit < (int)bs->pos)
                continue;
            n = mi->n;
            for (i = 0; i < n; i++) {
                CBENT *e = &tbl[i];
                if (e->id == (pss->pes.id & e->mask)) {
                    unsigned char *p;
                    cb.type = 6;
                    p = bs->base + (pss->pes.x28 >> 3);
                    if (p >= bs->end) p -= bs->size;
                    cb.data = p;
                    p = bs->base + (pss->pes.x20 >> 3);
                    if (p >= bs->end) p -= bs->size;
                    cb.pts = pss->pes.pts;
                    cb.data2 = p;
                    cb.len = pss->pes.len;
                    cb.dts = pss->pes.dts;
                    old = SetGP(e->gp);
                    cont = e->func(mp, &cb, e->data);
                    SetGP(old);
                    break;
                }
            }
            if (i == mi->n && func) {
                unsigned char *p;
                cb.type = 6;
                p = bs->base + (pss->pes.x28 >> 3);
                if (p >= bs->end) p -= bs->size;
                cb.data = p;
                p = bs->base + (pss->pes.x20 >> 3);
                if (p >= bs->end) p -= bs->size;
                cb.pts = pss->pes.pts;
                cb.data2 = p;
                cb.len = pss->pes.len;
                cb.dts = pss->pes.dts;
                old = SetGP(cbgp);
                cont = func(mp, &cb, cbdata);
                SetGP(old);
            }
            if (cont)
                result = (int)(bs->pos >> 3);
        }
        if (limit < (int)bs->pos)
            break;
        if ((int)(bs->buf >> 32) != 0x1BA)
            break;
        _pack_header(bs, &pss->hdr);
    }
    return result;
}

int sceMpegDemuxPssRing(MPEG *mp, unsigned char *addr, int size, unsigned char *buftop, int bufsize)
{
    BS bs;
    PSS pss;
    CBENT *tbl;
    MI *mi = mp->mi;
    int limit = size << 3;

    tbl = mi->tbl;
    bs.end = buftop + bufsize;
    bs.size = bufsize;
    bs.cur = addr;
    bs.base = addr;
    bs.pos = 0;
    bs.start = buftop;
    bs.buf = 0;
    bs.bits = 0;
    Fill(&bs);
    return Run(mp, mi, &bs, &pss, tbl, limit);
}
