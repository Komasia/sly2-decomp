/* InitSave (0x1AB128, Sly 1 save.c): the save manager's init: the card library and its MEMCARD (+0xFD5C), the port
 * and slot, no state (-1), wanted state 0, the times and the card info cleared. Layout: include/h5_mc.h (MC). */
struct SAVE {
    int port;
    int slot;
    int state;
    int stateWanted;
    float tState;
    float tPoll;
    int typeCard;
    int cclusterFree;
    int fFormatted;
};
extern "C" void sceMcInit(void) asm("sceMcInit");
extern "C" void InitMemcard(void *) asm("InitMemcard__FP7MEMCARD");
void InitSave(SAVE *psave, int port, int slot)
{
    sceMcInit();
    InitMemcard((char *)psave + 0xFD5C);
    psave->port = port;
    psave->slot = slot;
    psave->state = -1;
    psave->stateWanted = 0;
    psave->tState = psave->tPoll = 0.0f;
    psave->typeCard = 0;
    psave->cclusterFree = 0;
    psave->fFormatted = 0;
}
