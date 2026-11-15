/* IdPartCur: the screen object part the episode menu's mode plays (-1: none); the movie list's sub-modes have their
 * own table per movie. */
#include "h2_epmenu.h"
extern int *D_002BE1B8[];   /* per movie: the part of each sub-mode */
extern int *D_002BE080[];   /* per episode: the part of each mode */
// name: SafeHouse port (IdPartCur)
int IdPartCur__FP6EPMENU(EPMENU *pepmenu)
{
    int mode = pepmenu->mode;
    if (mode == -1)
        return -1;
    if (mode == EPMODE_Movies && pepmenu->sub != -1)
        return D_002BE1B8[pepmenu->imovie][pepmenu->sub];
    return D_002BE080[pepmenu->cur][pepmenu->mode];
}
