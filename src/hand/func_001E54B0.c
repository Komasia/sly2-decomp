/* func_001E54B0: releases the player-step object the script holds (pstepplayerMode, Lilly's name) through
 * func_0019CCE8 on its +0xF00 part, and forgets it. */
#include "relay.h"

void func_0019CCE8(void *pv);

void func_001E54B0(JSG *pjsg)
{
    char *pstepplayer = (char *)pjsg->pstepplayerMode;

    if (pstepplayer != NULL) {
        func_0019CCE8(pstepplayer + 0xF00);
        pjsg->pstepplayerMode = NULL;
    }
}
