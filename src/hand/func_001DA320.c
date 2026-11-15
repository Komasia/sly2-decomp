/* class: PROMPT, a HUD widget (SafeHouse hudwidget.cpp, orig 0x001DA320: the prompt's reset): no prompt shown or
 * asked for, no screen object, state Off. */
#include "h3_hud.h"
struct PROMPT {                   /* field: SafeHouse port (hudwidget.cpp PROMPT) */
    /* 0x00 */ char pad0[0x18];
    /* 0x18 */ int id;            /* the prompt shown */
    /* 0x1c */ float g;
    /* 0x20 */ int idNext;        /* the prompt asked for next */
    /* 0x24 */ float gNext;
    /* 0x28 */ void *pscreen;
};
void SetPromptState__FP6PROMPTi(struct PROMPT *pprompt, int state);

void func_001DA320(struct PROMPT *pprompt)
{
    pprompt->id = -1;
    pprompt->idNext = -1;
    pprompt->pscreen = 0;
    SetPromptState__FP6PROMPTi(pprompt, PROMPTS_Off);
}
