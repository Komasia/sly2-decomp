/* Sly 1 rumble.h: controller vibration. Sly 2's RUMBLE has no vtable slot at the front (nPort at +0). */
#ifndef RUMBLE_H
#define RUMBLE_H
#include "common.h"

enum RUMS { RUMS_Nil = -1, RUMS_Dead = 0, RUMS_Idle = 1, RUMS_Rumble = 2, RUMS_Stop = 3, RUMS_Kill = 4, RUMS_Max = 5 };

enum RUMK {
    RUMK_Nil = -1, RUMK_SteadyBuzz = 0, RUMK_LowThrob = 1, RUMK_MediumThrob = 2, RUMK_HardThrob = 3, RUMK_Blunt = 4,
    RUMK_Electric = 5, RUMK_Fire = 6, RUMK_Water = 7, RUMK_Crush = 8, RUMK_Break = 9, RUMK_Bomb = 10, RUMK_Max = 11
};

/* one step of a pattern: motor settings held for dt seconds */
struct RUMINS {
    /* 0x00 */ byte fHighSpeedMotor;
    /* 0x01 */ byte bLowSpeedMotor;
    /* 0x02 */ byte unk_0x02[2];
    /* 0x04 */ float dt;
};

struct RUMPAT {
    /* 0x00 */ int crumins;
    /* 0x04 */ RUMINS arumins[32];
};

struct RUMBLE {
    /* 0x00 */ int nPort;
    /* 0x04 */ int nSlot;
    /* 0x08 */ RUMS rums;
    /* 0x0c */ RUMPAT *prumpat;
    /* 0x10 */ int irumins;
    /* 0x14 */ float dtRumble;
    /* 0x18 */ float dtRumins;
};

void SetRumbleRums(RUMBLE *prumble, RUMS rums);
void InitRumble(RUMBLE *prumble, int nPort, int nSlot);

#endif
