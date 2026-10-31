/* CloneButton (Sly 1 button.c): clone the SO part; the BTN component then belongs to the clone. (Sly 2 no longer
 * keeps the pushed checkpoint across the clone.) */
#include "button.h"

void CloneSo(SO *pso, SO *psoBase);

void CloneButton(BUTTON *pbutton, BUTTON *pbuttonBase)
{
    CloneSo(&pbutton->so, &pbuttonBase->so);
    pbutton->btn.paloOwner = pbutton;
}
