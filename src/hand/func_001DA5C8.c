/* SetPromptState (SafeHouse hudwidget.cpp, orig 0x1DA5C8): change the prompt's state. Closing reopened in the same
 * frame goes straight to Shown; leaving Changing makes the next prompt current; Off forgets the prompt. On the
 * screen object: back from Changing plays WID_PROMPTIN, Changing plays WID_PROMPTCHANGE, Closing hides it (vt slot
 * 50) and Opening shows it with the prompt's id (func_00212880). */
#include "clock.h"
#include "h3_hud.h"
#include "vtbl.h"
typedef struct VT { VTENT a[64]; } VT;
typedef struct { char pad[0xC]; VT *vt; } LO;
typedef struct PROMPT {               /* field: SafeHouse port (hudwidget.cpp PROMPT) */
    /* 0x00 */ char pad[0x10];
    /* 0x10 */ int state;             /* PROMPTS */
    /* 0x14 */ float t;               /* the state's start (g_clock.t) */
    /* 0x18 */ int id;                /* the prompt shown */
    /* 0x1c */ float g;
    /* 0x20 */ int idNext;            /* the prompt asked for next */
    /* 0x24 */ float gNext;
    /* 0x28 */ LO *pscreen;           /* the screen object */
} PROMPT;
void StartPart__FP8SCREENRTi(LO *, int);
void func_00212880(LO *pscreen, int cid, int *aid);   /* show with arguments (SafeHouse ShowScreenObjArgs) */
// name: SafeHouse port (SetPromptState)
void SetPromptState__FP6PROMPTi(PROMPT *pprompt, int state)
{
    LO *pscreen;
    if (state == pprompt->state)
        return;
    switch (pprompt->state) {
    case PROMPTS_Closing:
        if (state == PROMPTS_Opening && pprompt->t == g_clock.t)
            state = PROMPTS_Shown;
        break;
    case PROMPTS_Changing:
        pprompt->id = pprompt->idNext;
        pprompt->g = pprompt->gNext;
        pprompt->idNext = -1;
        pprompt->gNext = -1.0f;
        break;
    }
    if (state == PROMPTS_Off)
        pprompt->id = -1;
    pscreen = pprompt->pscreen;
    if (pscreen) {
        if (pprompt->state == PROMPTS_Changing && state == PROMPTS_Shown)
            StartPart__FP8SCREENRTi(pscreen, WID_PROMPTIN);
        switch (state) {
        case PROMPTS_Changing:
            StartPart__FP8SCREENRTi(pprompt->pscreen, WID_PROMPTCHANGE);
            break;
        case PROMPTS_Closing:
            ((void (*)(void *))pprompt->pscreen->vt->a[50].pfn)(VT_THIS(pprompt->pscreen, &pprompt->pscreen->vt->a[50]));
            break;
        case PROMPTS_Opening:
            func_00212880(pprompt->pscreen, 1, &pprompt->id);
            break;
        }
    }
    pprompt->state = state;
    pprompt->t = g_clock.t;
}
