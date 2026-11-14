/* class: SAVE (UpdateSave calls it): whether its +0x114 is set. */
typedef struct SAVE {
    /* 0x000 */ char pad0[0x114];
    /* 0x114 */ int n114;
} SAVE;

int func_001B42C0(SAVE *psave)
{
    return psave->n114 != 0;
}
