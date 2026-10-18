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
    int packetLength;
    int scrambling;
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
    __asm__ volatile("move %0, $gp\n\tmove $gp, %1" : "=&r"(old) : "r"(gp) : "$28", "memory");
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
    { \
        unsigned char *packetp = bs->base + (pss->pes.x28 >> 3); \
        cb.type = 6; \
        if (packetp >= bs->end) packetp -= bs->size; \
        cb.data = packetp; \
    } \
    { \
        unsigned char *payloadp = bs->base + (pss->pes.x20 >> 3); \
        if (payloadp >= bs->end) payloadp -= bs->size; \
        cb.pts = pss->pes.pts; \
        cb.data2 = payloadp; \
    } \
    cb.len = pss->pes.len; \
    cb.dts = pss->pes.dts; \
    old = SetGP(G); \
    cont = (F)(mp, &cb, (D)); \
    SetGP(old); \
} while (0)

typedef char pss_int4[(sizeof(int)==4)?1:-1];
typedef char pss_ptr4[(sizeof(void*)==4)?1:-1];
typedef char pss_long8[(sizeof(unsigned long)==8)?1:-1];
typedef char pss_longalign8[(__alignof__(unsigned long)==8)?1:-1];
typedef char pss_bs40[(sizeof(BS)==40)?1:-1];
typedef char pss_bsalign8[(__alignof__(BS)==8)?1:-1];
typedef char pss_hdr16[(sizeof(HEADER)==16)?1:-1];
typedef char pss_hdralign4[(__alignof__(HEADER)==4)?1:-1];
typedef char pss_pes48[(sizeof(PES)==48)?1:-1];
typedef char pss_pesalign8[(__alignof__(PES)==8)?1:-1];
typedef char pss_pss72[(sizeof(PSS)==72)?1:-1];
typedef char pss_pssalign8[(__alignof__(PSS)==8)?1:-1];
typedef char pss_cb32[(sizeof(CBDATA)==32)?1:-1];
typedef char pss_cbalign8[(__alignof__(CBDATA)==8)?1:-1];
typedef char pss_ent32[(sizeof(CBENT)==32)?1:-1];
typedef char pss_entalign8[(__alignof__(CBENT)==8)?1:-1];
typedef char pss_mi104[(sizeof(MI)==104)?1:-1];
typedef char pss_mialign4[(__alignof__(MI)==4)?1:-1];
typedef char pss_mp68[(sizeof(MPEG)==68)?1:-1];
typedef char pss_mpalign4[(__alignof__(MPEG)==4)?1:-1];
typedef char pss_BS_buf[(((unsigned long)&((BS*)0)->buf)==0)?1:-1];
typedef char pss_BS_pos[(((unsigned long)&((BS*)0)->pos)==8)?1:-1];
typedef char pss_BS_base[(((unsigned long)&((BS*)0)->base)==16)?1:-1];
typedef char pss_BS_cur[(((unsigned long)&((BS*)0)->cur)==20)?1:-1];
typedef char pss_BS_bits[(((unsigned long)&((BS*)0)->bits)==24)?1:-1];
typedef char pss_BS_start[(((unsigned long)&((BS*)0)->start)==28)?1:-1];
typedef char pss_BS_end[(((unsigned long)&((BS*)0)->end)==32)?1:-1];
typedef char pss_BS_size[(((unsigned long)&((BS*)0)->size)==36)?1:-1];
typedef char pss_PES_id[(((unsigned long)&((PES*)0)->id)==0)?1:-1];
typedef char pss_PES_packetLength[(((unsigned long)&((PES*)0)->packetLength)==8)?1:-1];
typedef char pss_PES_scrambling[(((unsigned long)&((PES*)0)->scrambling)==12)?1:-1];
typedef char pss_PES_pts[(((unsigned long)&((PES*)0)->pts)==16)?1:-1];
typedef char pss_PES_dts[(((unsigned long)&((PES*)0)->dts)==24)?1:-1];
typedef char pss_PES_x20[(((unsigned long)&((PES*)0)->x20)==32)?1:-1];
typedef char pss_PES_len[(((unsigned long)&((PES*)0)->len)==36)?1:-1];
typedef char pss_PES_x28[(((unsigned long)&((PES*)0)->x28)==40)?1:-1];
typedef char pss_PSS_hdr[(((unsigned long)&((PSS*)0)->hdr)==0)?1:-1];
typedef char pss_PSS_pes[(((unsigned long)&((PSS*)0)->pes)==24)?1:-1];
typedef char pss_CBDATA_type[(((unsigned long)&((CBDATA*)0)->type)==0)?1:-1];
typedef char pss_CBDATA_data[(((unsigned long)&((CBDATA*)0)->data)==4)?1:-1];
typedef char pss_CBDATA_data2[(((unsigned long)&((CBDATA*)0)->data2)==8)?1:-1];
typedef char pss_CBDATA_len[(((unsigned long)&((CBDATA*)0)->len)==12)?1:-1];
typedef char pss_CBDATA_pts[(((unsigned long)&((CBDATA*)0)->pts)==16)?1:-1];
typedef char pss_CBDATA_dts[(((unsigned long)&((CBDATA*)0)->dts)==24)?1:-1];
typedef char pss_CBENT_id[(((unsigned long)&((CBENT*)0)->id)==0)?1:-1];
typedef char pss_CBENT_mask[(((unsigned long)&((CBENT*)0)->mask)==8)?1:-1];
typedef char pss_CBENT_func[(((unsigned long)&((CBENT*)0)->func)==16)?1:-1];
typedef char pss_CBENT_data[(((unsigned long)&((CBENT*)0)->data)==20)?1:-1];
typedef char pss_CBENT_gp[(((unsigned long)&((CBENT*)0)->gp)==24)?1:-1];
typedef char pss_MI_tbl[(((unsigned long)&((MI*)0)->tbl)==96)?1:-1];
typedef char pss_MI_n[(((unsigned long)&((MI*)0)->n)==100)?1:-1];
typedef char pss_MPEG_mi[(((unsigned long)&((MPEG*)0)->mi)==64)?1:-1];

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
    register MI *mi asm("$20") = mp->mi;
    register int limit asm("$22") = size << 3;
    CBFUNC func = 0;
    register int cont asm("$21") = 1;
    int i;
    void *old;

    tbl = mi->tbl;
    bsbuf.size = bufsize;
    bsbuf.base = addr;
    bsbuf.cur = addr;
    bsbuf.pos = 0;
    cbdata = 0;
    bsbuf.start = buftop;
    result = 0;
    bsbuf.end = buftop + bufsize;
    cbgp = 0;
    bsbuf.buf = 0;
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
    while ((bs->buf >> 40) == 1 && (int)(bs->buf >> 32) != 0x1BA && (int)(bs->buf >> 32) != 0x1B9) {
        if (!((int)bs->pos < limit)) goto out;
        if (!cont) goto out;
        _PES_packet(mi, bs, &pss->pes);
        if (limit < (int)bs->pos) continue;
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
    }
out:
    if (!(limit < (int)bs->pos) && (int)(bs->buf >> 32) == 0x1BA) goto again;
    return result;
}
