/* The carried state's transitions (state 8, Bentley's +0x1800): thrown (1) and on a support again (+0x208), he
 * stands (state 0) and vt slot 79 is told 1. */
#include "vtbl.h"
struct BENTLEY { int pad[3]; VTENT *vt; char pad2[0x208 - 0x10]; int psupport; char pad3[0x1800 - 0x20c]; int n1800; };
void SetBentleyState__FP7BENTLEYi(struct BENTLEY *, int);
void func_001367D8(struct BENTLEY *pbentley) {
    int n1800Old;
    do {
        n1800Old = pbentley->n1800;
        switch (n1800Old) {
        case 0: break;
        case 1:
            if (pbentley->psupport) {
                SetBentleyState__FP7BENTLEYi(pbentley, 0);
                ((void (*)(void *, int))pbentley->vt[79].pfn)(VT_THIS(pbentley, &pbentley->vt[79]), 1);
            }
            break;
        }
    } while (pbentley->n1800 != n1800Old && pbentley->n1800 != -1);
}
