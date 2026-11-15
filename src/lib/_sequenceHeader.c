// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
#include "ee_regs.h"
/* _sequenceHeader (libmpeg): parse an MPEG sequence_header(): picture size, bit rate, VBV size, and load the
   intra / non-intra quantiser matrices into the IPU (the stream's own, or the default tables by DMA). */
#define IPU_CMD_SETIQ_INTRA    0x50000000   /* SETIQ, intra matrix */
#define IPU_CMD_SETIQ_NONINTRA 0x58000000   /* SETIQ, non-intra matrix */
#define MPEG_MAX_VSIZE 2800
typedef struct { int type; int pad[7]; } CB;
typedef struct {
    char p0[0xE8]; int xE8;         /* 0xE8 picture-structure filter, reset per sequence */
    char pEC[0x134 - 0xEC]; int hsize; int vsize;
    char p13C[0x144 - 0x13C]; int bit_rate; int vbv_size;  /* 0x144 */
    char p14C[0x828 - 0x14C]; int top_invalid; unsigned int cmd;  /* 0x828 IPU_TOP stale, last IPU command class */
    char p830[0x850 - 0x830]; int load_intra; int load_nonintra;
    char p858[0x868 - 0x858]; void *mp;
} D;
#define R(a) (*(volatile unsigned int *)(a))
extern unsigned char D_002C84C0[];  /* default intra quantiser matrix */
extern unsigned char D_002C8500[];  /* default non-intra quantiser matrix */
unsigned int _sceMpegNextBit(D *d, int n);
void _sceMpegError(D *d, const char *msg);
int _sceMpegDispatchMpegCallback(void *mp, CB *cb);
void _waitIpuIdle_254488(D *d);
#define _waitIpuIdle _waitIpuIdle_254488   /* this object's own static copy */
int DIntr(void);
int EIntr(void);
void _extensionAndUserData(D *d);
void _initSeq(void *mp);
static inline void _loadQM(D *d, unsigned char *qm, unsigned int cmd)
{
    CB cb;
    int e;

    cb.type = 2;
    _sceMpegDispatchMpegCallback(d->mp, &cb);
    _waitIpuIdle(d);
    R(IPU_CMD_ADDR) = 0;
    _waitIpuIdle(d);
    e = DIntr();
    R(D4_MADR_ADDR) = (unsigned int)qm & 0x0FFFFFFF;    /* toIPU: 4 qwords = 64 bytes */
    R(D4_QWC_ADDR) = 4;
    R(D4_CHCR_ADDR) = D_CHCR_STR_BIT | D_CHCR_DIR_FROM_MEM;
    if (e)
        EIntr();
    R(IPU_CMD_ADDR) = cmd;
    d->cmd = cmd & 0xF0000000;
    d->top_invalid = 1;
    _waitIpuIdle(d);
    cb.type = 3;
    _sceMpegDispatchMpegCallback(d->mp, &cb);
}
void _sequenceHeader(D *d)
{
    unsigned int v;
    int vs;

    d->xE8 = 0;
    v = _sceMpegNextBit(d, 32);
    vs = (v >> 8) & 0xFFF;
    d->hsize = v >> 20;
    d->vsize = vs;
    if (vs > MPEG_MAX_VSIZE)
        _sceMpegError(d, "vertical size > 2800");
    v = _sceMpegNextBit(d, 30);
    d->bit_rate = v >> 12;
    d->vbv_size = (v >> 1) & 0x3FF;
    if ((d->load_intra = _sceMpegNextBit(d, 1))) {
        _waitIpuIdle(d);
        R(IPU_CMD_ADDR) = IPU_CMD_SETIQ_INTRA;   /* matrix follows in the bitstream */
        d->cmd = IPU_CMD_SETIQ_INTRA;
        d->top_invalid = 1;
        _waitIpuIdle(d);
    } else {
        _loadQM(d, D_002C84C0, IPU_CMD_SETIQ_INTRA);
    }
    if ((d->load_nonintra = _sceMpegNextBit(d, 1))) {
        _waitIpuIdle(d);
        R(IPU_CMD_ADDR) = IPU_CMD_SETIQ_NONINTRA;
        d->cmd = IPU_CMD_SETIQ_INTRA;     /* (sic) only the command class matters */
        d->top_invalid = 1;
        _waitIpuIdle(d);
    } else {
        _loadQM(d, D_002C8500, IPU_CMD_SETIQ_NONINTRA);
    }
    _extensionAndUserData(d);
    _initSeq(d->mp);
}
