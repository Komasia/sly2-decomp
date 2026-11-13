/* class: PROMPT, a HUD widget (SafeHouse hudwidget.cpp, orig 0x001DA320: the prompt's reset): +0x18 / +0x20 -1,
 * +0x28 0, state 0. */
struct PROMPT {
    /* 0x00 */ char pad0[0x18];
    /* 0x18 */ int n18;
    /* 0x1c */ int pad1c;
    /* 0x20 */ int n20;
    /* 0x24 */ int pad24;
    /* 0x28 */ int n28;
};
void SetPromptState__FP6PROMPTi(struct PROMPT *pprompt, int state);

void func_001DA320(struct PROMPT *pprompt)
{
    pprompt->n18 = -1;
    pprompt->n20 = -1;
    pprompt->n28 = 0;
    SetPromptState__FP6PROMPTi(pprompt, 0);
}
