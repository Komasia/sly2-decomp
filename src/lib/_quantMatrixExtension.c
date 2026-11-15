// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
#include "ee_regs.h"
typedef struct {
    char p0[0x828]; int top_invalid; unsigned int cmd;   /* 0x828 */ char p1[0x850 - 0x830]; int load_iq; int load_niq;
} MpegD;
extern char D_002AC728[];
extern char D_002AC750[];
int _sceMpegNextBit(MpegD *d, int n);
void _waitIpuIdle_254488(MpegD *d);
void _sceMpegError(MpegD *d, const char *msg);
/* _quantMatrixExtension (libmpeg): parse quant_matrix_extension(): load the intra / non-intra matrices that
   follow into the IPU (SETIQ reads them from the bitstream); chroma matrices are not supported. */
void _quantMatrixExtension(MpegD *d)
{
    if ((d->load_iq = _sceMpegNextBit(d, 1)) != 0) {
        _waitIpuIdle_254488(d);
        EE_REG(IPU_CMD_ADDR) = IPU_CMD_SETIQ;
        d->cmd = IPU_CMD_SETIQ;
        d->top_invalid = 1;
        _waitIpuIdle_254488(d);
    }
    if ((d->load_niq = _sceMpegNextBit(d, 1)) != 0) {
        _waitIpuIdle_254488(d);
        EE_REG(IPU_CMD_ADDR) = IPU_CMD_SETIQ | 0x08000000;  /* non-intra */
        d->cmd = IPU_CMD_SETIQ;
        d->top_invalid = 1;
        _waitIpuIdle_254488(d);
    }
    if (_sceMpegNextBit(d, 1)) _sceMpegError(d, D_002AC728);
    if (_sceMpegNextBit(d, 1)) _sceMpegError(d, D_002AC750);
}
