/* func_001C4728 (0x1C4728): is any of the given buttons held on this controller? */
#include "po.h"

int func_001C4728(POCTL *pctl, uint grfbtn)
{
    return (pctl->grfbtn & grfbtn) != 0;
}
