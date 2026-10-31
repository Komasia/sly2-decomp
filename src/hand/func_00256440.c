/* func_00256440: constructor of MURRAY (class 54; g++'s out-of-line copy of the inline constructor, used by the
 * class factory func_00111700). As for JT (func_002563E8): SO vtable, GLOBSET member (+0x80), PO field +0x174,
 * then the MURRAY vtable; finally its class-145 member at +0x1890 is constructed (func_0020C058). */
#include "po.h"

typedef struct MURRAY {
    /* 0x0000 */ PO po;
    /* 0x0180 */ char unk_0x180[0x1890 - 0x180];
    /* 0x1890 */ char unk_0x1890[0x70];   /* class 145 object */
} MURRAY;

extern VTE g_vtso[];
extern VTE g_vtmurray[];
void *__4CRef(void *pglobset);     /* GLOBSET constructor (0x167310; the symbol name is a misnomer) */
void *func_0020C058(void *p);      /* class 145 constructor */

MURRAY *func_00256440(MURRAY *pmurray)
{
    pmurray->po.so.lo.pframe = NULL;
    pmurray->po.so.lo.psidebag = NULL;
    pmurray->po.so.lo.pvt = g_vtso;
    __4CRef(pmurray->po.so.globset);
    pmurray->po.unk_0x170[1] = 0;
    pmurray->po.so.lo.pvt = g_vtmurray;
    func_0020C058(pmurray->unk_0x1890);
    return pmurray;
}
