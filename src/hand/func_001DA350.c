/* UpdatePrompt (SafeHouse hudwidget.cpp, orig 0x1DA350): advance the prompt: Opening -> Shown once its screen object
 * is open (+0x58 state 2); Shown changes to the next prompt, closes when its time is 0, and holds its start time
 * while hidden; Closing -> Off once closed; Changing -> Shown (or Off) when the change animation ends. */
#include "clock.h"
#include "h3_hud.h"
typedef struct { char pad[0x58]; int x58; } W;
typedef struct PROMPT {               /* field: SafeHouse port (hudwidget.cpp PROMPT) */
    /* 0x00 */ char pad[0x10];
    /* 0x10 */ int state;             /* PROMPTS */
    /* 0x14 */ float t;               /* the state's start (g_clock.t) */
    /* 0x18 */ int id;                /* the prompt shown */
    /* 0x1c */ float g;               /* its time (0: closes, < 0: stays) */
    /* 0x20 */ int idNext;            /* the prompt asked for next (-1: none) */
    /* 0x24 */ float gNext;
    /* 0x28 */ W *pw;                 /* the screen object */
} PROMPT;
void SetPromptState__FP6PROMPTi(PROMPT *pprompt, int state);
int FVisible__FP8SCREENRT(W *);
int FSpriteAnimPlaying__FP2LOi(W *, int);
// name: SafeHouse port (UpdatePrompt)
void UpdatePrompt__FP6PROMPT(PROMPT *pprompt)
{
    if (pprompt->pw == 0)
        return;
    switch (pprompt->state) {
    case PROMPTS_Off:
        break;
    case PROMPTS_Opening:
        if (pprompt->pw->x58 == 2)
            SetPromptState__FP6PROMPTi(pprompt, PROMPTS_Shown);
        break;
    case PROMPTS_Shown:
        if (pprompt->idNext != -1) {
            SetPromptState__FP6PROMPTi(pprompt, PROMPTS_Changing);
        } else if (pprompt->g == 0.0f) {
            SetPromptState__FP6PROMPTi(pprompt, PROMPTS_Closing);
        } else if (0.0f < pprompt->g) {
            if (pprompt->pw && !FVisible__FP8SCREENRT(pprompt->pw))
                pprompt->t += g_clock.dt;
        }
        break;
    case PROMPTS_Closing:
        if (pprompt->pw->x58 < 2)
            SetPromptState__FP6PROMPTi(pprompt, PROMPTS_Off);
        break;
    case PROMPTS_Changing:
        if (FSpriteAnimPlaying__FP2LOi(pprompt->pw, WID_PROMPTCHANGE))
            break;
        if (pprompt->idNext == -1)
            SetPromptState__FP6PROMPTi(pprompt, PROMPTS_Off);
        else
            SetPromptState__FP6PROMPTi(pprompt, PROMPTS_Shown);
        break;
    }
}
