/* func_002563E8: constructor of JT (class 53, the player character; g++'s out-of-line copy of the inline
 * constructor, used by the class factory func_001116D8). The SO part gets the SO vtable while its GLOBSET member
 * (+0x80) is constructed (GLOBSET::GLOBSET, 0x167310), the PO part clears its field at +0x174, then
 * the JT vtable goes in and the gadget sound reference is cleared. Layout after Lilly's JT. */
#include "po.h"

typedef struct JT {
    /* 0x0000 */ PO po;
    /* 0x0180 */ char unk_0x180[0x2044 - 0x180];
    /* 0x2044 */ void *psndGadget;     /* CRefPtr<SND> */
    /* 0x2048 */ int unk_0x2048;
} JT;

extern VTE g_vtso[];
extern VTE g_vtjt[];
void *__7GLOBSET(void *pglobset);   /* GLOBSET::GLOBSET() (0x167310) */

JT *func_002563E8(JT *pjt)
{
    pjt->po.so.lo.pframe = NULL;
    pjt->po.so.lo.psidebag = NULL;
    pjt->po.so.lo.pvt = g_vtso;
    __7GLOBSET(pjt->po.so.globset);
    pjt->po.unk_0x170[1] = 0;
    pjt->po.so.lo.pvt = g_vtjt;
    pjt->psndGadget = NULL;
    pjt->unk_0x2048 = 0;
    return pjt;
}
