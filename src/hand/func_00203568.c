/* InitPhotoTarget (0x203568): PHOTOTARGET vt slot 7: the XFM init, then no title, list title, dialog or message. */
#include "h6_photo.h"

void InitXfm__FP3XFM(PHOTOTARGET *ptarget);

// name: SafeHouse port (InitPhotoTarget)
void InitPhotoTarget__FP2LO(PHOTOTARGET *ptarget)
{
    InitXfm__FP3XFM(ptarget);
    ptarget->title = -1;
    ptarget->message = -1;
    ptarget->dialog = -1;
    ptarget->listTitle = -2;
}
