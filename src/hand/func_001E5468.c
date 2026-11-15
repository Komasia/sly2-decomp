/* func_001E5468: the script lets go of the widget it showed (vt slot 50) and forgets it. */
#include "relay.h"
struct WIDGET { char pad[0xC]; VTENT *vt; };
void func_001E5468(JSG *pjsg)
{
    struct WIDGET *pwidget = pjsg->ploWidget;
    if (pwidget) {
        ((void (*)(void *))pwidget->vt[50].pfn)(VT_THIS(pwidget, &pwidget->vt[50]));
        pjsg->ploWidget = 0;
    }
}
