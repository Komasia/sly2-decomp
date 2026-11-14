/* A pursued object's record (SafeHouse aipursuit.h: orig 0xAC bytes, 0x20A5F8, listed at 0x3E145C): its object, the
 * gains 1 / 2, -1 ids, then on the list. */
#include "so.h"
struct LO;
struct PURSUIT {
    /* 0x00 */ DLE dle;
    /* 0x08 */ int n8;
    /* 0x0c */ struct LO *plo;
    /* 0x10 */ int n10;
    /* 0x14 */ float g14;
    /* 0x18 */ float g18;
};
extern DL D_003E145C;   /* the pursued objects */
void AppendDlEntry__FP2DLPv(DL *pdl, void *pv);

struct PURSUIT *func_0020A5F8(struct PURSUIT *ppursuit, struct LO *plo)
{
    ppursuit->plo = plo;
    ppursuit->g14 = 1.0f;
    ppursuit->g18 = 2.0f;
    ppursuit->n10 = -1;
    ppursuit->n8 = -1;
    AppendDlEntry__FP2DLPv(&D_003E145C, ppursuit);
    return ppursuit;
}
