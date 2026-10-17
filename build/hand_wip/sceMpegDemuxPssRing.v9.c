// WIP v9 (Claude agent sony7, 2026-10-17): aligned 23 (v8 48, v7 67). v8 + `do { _PES_packet(...); } while (0);` (loop-depth ref weight: mi/cont/limit
// get s4/s5/s6 like the target), &tbl[i] as (CBENT *)((i << 5) + (int)tbl) (target addu order), bs init order size,cur,base,cbdata,pos,start,result,end,buf,cbgp,bits,
// pss = &pssbuf before Fill(). Left: first `== 0x1BA` bne slot (ours copies dsrl32 from the taken thread, +1 insn -> loop: .p2align nop), cur/base +
// local-init store order, `limit < pos` do/while(0) makes that branch predicted not-taken (target bnel); removing it drops limit to fp.
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


#define CALLBACK(F, D, G) do { \
    unsigned char *p; \
    p = bs->base + (pss->pes.x28 >> 3); \
    cb.type = 6; \
    if (p >= bs->end) p -= bs->size; \
    cb.data = p; \
    p = bs->base + (pss->pes.x20 >> 3); \
    if (p >= bs->end) p -= bs->size; \
    cb.pts = pss->pes.pts; \
    cb.data2 = p; \
    cb.len = pss->pes.len; \
    cb.dts = pss->pes.dts; \
    old = SetGP(G); \
    cont = (F)(mp, &cb, (D)); \
    SetGP(old); \
} while (0)

int sceMpegDemuxPssRing(MPEG *mp, unsigned char *addr, int size, unsigned char *buftop, int bufsize)
{
    BS bsbuf;
    PSS pssbuf;
    CBDATA cb;
    void *cbdata;
    CBENT *tbl;
    int result;
    void *cbgp;
    BS *bs;
    PSS *pss;
    MI *mi = mp->mi;
    int limit = size << 3;
    CBFUNC func = 0;
    int cont = 1;
    int i, n;
    void *old;

    tbl = mi->tbl;
    bsbuf.size = bufsize;
    bsbuf.cur = addr;
    bsbuf.base = addr;
    cbdata = 0;
    bsbuf.pos = 0;
    bsbuf.start = buftop;
    result = 0;
    bsbuf.end = buftop + bufsize;
    bsbuf.buf = 0;
    cbgp = 0;
    bsbuf.bits = 0;
    pss = &pssbuf;
    Fill(&bsbuf);
    bs = &bsbuf;

    i = 0;
    if (mi->n > 0) do {
        CBENT *e = (CBENT *)((i << 5) + (int)tbl);
        if (e->id == 0xBDFF000000) {
            func = e->func;
            cbdata = e->data;
            cbgp = e->gp;
        }
        if (func) break;
        i++;
    } while (i < mi->n);
    if ((int)(bs->buf >> 32) == 0x1BA) {
again:
        _pack_header(bs, &pss->hdr);
    }
    if ((bs->buf >> 40) != 1 || (int)(bs->buf >> 32) == 0x1BA || (int)(bs->buf >> 32) == 0x1B9)
        goto out;
loop:
    do { if (!((int)bs->pos < limit)) goto out; } while (0);
    if (!cont) goto out;
    do { _PES_packet(mi, bs, &pss->pes); } while (0);
    do { if (limit < (int)bs->pos) goto bottom; } while (0);
    for (i = 0; i < mi->n; i++) {
        CBENT *e = (CBENT *)((i << 5) + (int)tbl);
        if (e->id == (pss->pes.id & e->mask)) {
            CALLBACK(e->func, e->data, e->gp);
            break;
        }
    }
    if (i == mi->n && func)
        CALLBACK(func, cbdata, cbgp);
    if (cont)
        result = (int)(bs->pos >> 3);
bottom:
    if ((bs->buf >> 40) == 1 && (int)(bs->buf >> 32) != 0x1BA && (int)(bs->buf >> 32) != 0x1B9)
        goto loop;
out:
    do { if (!(limit < (int)bs->pos) && (int)(bs->buf >> 32) == 0x1BA) goto again; } while (0);
    return result;
}
