#include "clock.h"
typedef struct { char pad[0x58]; int x58; } W;
typedef struct {
    char pad[0x10];
    int state;
    float t;
    int x18;
    float x1C;
    int x20;
    float x24;
    W *pw;
} OBJ;
void SetPromptState__FP6PROMPTi(OBJ *, int);
int FVisible__FP8SCREENRT(W *);
int FSpriteAnimPlaying__FP2LOi(W *, int);
// name: SafeHouse port (UpdatePrompt)
void UpdatePrompt__FP6PROMPT(OBJ *p)
{
    if (p->pw == 0)
        return;
    switch (p->state) {
    case 0:
        break;
    case 1:
        if (p->pw->x58 == 2)
            SetPromptState__FP6PROMPTi(p, 2);
        break;
    case 2:
        if (p->x20 != -1) {
            SetPromptState__FP6PROMPTi(p, 4);
        } else if (p->x1C == 0.0f) {
            SetPromptState__FP6PROMPTi(p, 3);
        } else if (0.0f < p->x1C) {
            if (p->pw && !FVisible__FP8SCREENRT(p->pw))
                p->t += g_clock.dt;
        }
        break;
    case 3:
        if (p->pw->x58 < 2)
            SetPromptState__FP6PROMPTi(p, 0);
        break;
    case 4:
        if (FSpriteAnimPlaying__FP2LOi(p->pw, 0x312))
            break;
        if (p->x20 == -1)
            SetPromptState__FP6PROMPTi(p, 0);
        else
            SetPromptState__FP6PROMPTi(p, 2);
        break;
    }
}
