/* RefreshScreenObj: a screen object shown idle (state 2) starts its idle time again (+0x5C = the real clock).
 * SCREENOBJ run-time state: SafeHouse port (screenrt.h: "orig: 0x00212A30: shown idle (state 2): its idle time
 * (+0x5C, against +0x8C) starts again"). */
struct SCREENOBJ {
    /* 0x00 */ char pad0[0x58];
    /* 0x58 */ int state;        /* field: SafeHouse port - 0 not loaded, 1 stopped, 2 idle, 3 show, 4 hide */
    /* 0x5c */ float tState;     /* field: SafeHouse port */
};
extern float D_002DDF0C;         /* the real clock's time (CLOCK +0x3C) */

// name: SafeHouse port (RefreshScreenObj)
void RefreshScreenObj__FP2LO(struct SCREENOBJ *pscrobj)
{
    if (pscrobj->state == 2)
        pscrobj->tState = D_002DDF0C;
}
