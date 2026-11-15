/* class: PROMPT, a HUD widget (SafeHouse hudwidget.cpp): ask for prompt id for time g (-1: withdraw all, see
 * func_001DA578). Off / Closing (and Opening, restarted) show it now; Shown with the same prompt only updates its
 * time; otherwise (Shown, Changing) it is queued as the next prompt. */
#include "h3_hud.h"
typedef struct PROMPT {               /* field: SafeHouse port (hudwidget.cpp PROMPT) */
    /* 0x00 */ char pad[0x10];
    /* 0x10 */ int state;             /* PROMPTS */
    /* 0x14 */ int pad14;
    /* 0x18 */ int id;
    /* 0x1c */ float g;
    /* 0x20 */ int idNext;
    /* 0x24 */ float gNext;
} PROMPT;
void func_001DA578(PROMPT *pprompt, int id);
void SetPromptState__FP6PROMPTi(PROMPT *pprompt, int state);

void func_001DA4B8(PROMPT *pprompt, int id, float g)
{
    if (id == -1) {
        func_001DA578(pprompt, -1);
        return;
    }
    switch (pprompt->state) {
    case PROMPTS_Opening:
        SetPromptState__FP6PROMPTi(pprompt, PROMPTS_Nil);
    case PROMPTS_Off:
    case PROMPTS_Closing:
        pprompt->id = id;
        pprompt->g = g;
        SetPromptState__FP6PROMPTi(pprompt, PROMPTS_Opening);
        break;
    case PROMPTS_Shown:
        if (pprompt->id == id) {
            pprompt->g = g;
            break;
        }
    case PROMPTS_Changing:
        pprompt->idNext = id;
        pprompt->gNext = g;
        break;
    }
}
