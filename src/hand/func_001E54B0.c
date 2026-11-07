/* func_001E54B0: releases the player-step object the script holds (pstepplayerMode, Lilly's name) through
 * CloseBinoc__FP5ACTOR on its +0xF00 part, and forgets it. */
#include "relay.h"

void CloseBinoc__FP5ACTOR(void *pv);

void func_001E54B0(JSG *pjsg)
{
    char *pstepplayer = (char *)pjsg->pstepplayerMode;

    if (pstepplayer != NULL) {
        CloseBinoc__FP5ACTOR(pstepplayer + 0xF00);
        pjsg->pstepplayerMode = NULL;
    }
}
