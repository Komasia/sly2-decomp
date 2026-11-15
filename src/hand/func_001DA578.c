/* class: PROMPT, a HUD widget (SafeHouse hudwidget.cpp): withdraw prompt id (-1: every prompt): the shown one gets
 * time 0 (it closes), a queued one is dropped. */
struct PROMPT {                       /* field: SafeHouse port (hudwidget.cpp PROMPT) */
    /* 0x00 */ char pad[0x18];
    /* 0x18 */ int id;
    /* 0x1c */ int g;                 /* (time 0 stored as an integer) */
    /* 0x20 */ int idNext;
};

void func_001DA578(struct PROMPT *pprompt, int id)
{
    if (id == -1) {
        pprompt->idNext = -1;
        pprompt->g = 0;
    } else if (id == pprompt->id) {
        pprompt->g = 0;
    } else if (id == pprompt->idNext) {
        pprompt->idNext = -1;
    }
}
