/* IdHudPrompt: the HUD prompt asked for next, or the one shown when none is asked for.
 * name: SafeHouse port (hudwidget.h "int IdHudPrompt(); // 0x1DA5B0"; hudwidget.cpp: "the prompt asked for next,
 * else the one shown"); the argument is the PROMPT (as UpdatePrompt__FP6PROMPT / SetPromptState__FP6PROMPTi). */
struct PROMPT {
    /* 0x00 */ char pad0[0x18];
    /* 0x18 */ int id;        /* field: SafeHouse port - the prompt shown */
    /* 0x1C */ int pad1C;
    /* 0x20 */ int idNext;    /* field: SafeHouse port - the prompt asked for next (-1: none) */
};

int IdHudPrompt__FP6PROMPT(struct PROMPT *pprompt)
{
    int id = pprompt->idNext;
    if (id == -1)
        id = pprompt->id;
    return id;
}
