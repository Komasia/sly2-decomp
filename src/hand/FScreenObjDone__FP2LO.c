/* FScreenObjDone: whether a screen object is done: stopped or not loaded (+0x58 < 2) and no show / hide timer
 * running (+0x64 < 2). SCREENOBJ run-time state: SafeHouse port (screenrt.cpp). */
struct SCREENOBJ {
    /* 0x00 */ char pad0[0x58];
    /* 0x58 */ int state;        /* field: SafeHouse port - 0 not loaded, 1 stopped, 2 idle, 3 show, 4 hide */
    /* 0x5c */ float tState;     /* field: SafeHouse port */
    /* 0x60 */ int pad60;
    /* 0x64 */ int timers;       /* field: SafeHouse port - 1 hide, 2 show */
};

// name: SafeHouse port (FScreenObjDone)
int FScreenObjDone__FP2LO(struct SCREENOBJ *pscrobj)
{
    int fDone = 0;
    if (pscrobj->state < 2)
        fDone = pscrobj->timers < 2;
    return fDone;
}
