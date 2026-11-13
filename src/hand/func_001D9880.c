/* A HUD widget shown (SafeHouse menu.h FMenuShown / FCardMessageActive, orig 0x001D9880): in the widget list
 * D_003D9E70. */
#include "so.h"
extern DL D_003D9E70;   /* the HUD's widgets */
int FFindDlEntry__FP2DLPv(DL *pdl, void *pv);

int func_001D9880(void *pwidget)
{
    return FFindDlEntry__FP2DLPv(&D_003D9E70, pwidget);
}
