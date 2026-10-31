/* BOMB (class 79, derived from SO) and MISSILE (class 80, derived from BOMB; classes 81/82 derive from MISSILE);
 * partial layouts. */
#ifndef BOMB_H
#define BOMB_H
#include "so.h"

typedef struct BOMB {
    /* 0x000 */ SO so;
    /* 0x150 */ char unk_0x150[0xB0];
    /* 0x200 */ SO *psoOwner;          /* set through func_0013BC60, which re-registers the bomb with the world */
    /* 0x204 */ char unk_0x204[0xC];
} BOMB;   /* 0x210 bytes */

typedef struct MISSILE {
    /* 0x000 */ BOMB bomb;
    /* 0x210 */ char unk_0x210[0x50];
    /* 0x260 */ float sUnk260;         /* 800 after InitMissile */
    /* 0x264 */ int fUnk264;           /* 1 after InitMissile; class 81 clears it */
    /* 0x268 */ char unk_0x268[4];     /* sub-object passed to func_0012E460 */
    /* 0x26c */ float gUnk26c;         /* 1.0 after InitMissile */
    /* 0x270 */ float sUnk270;         /* class 81: 2000 */
    /* 0x274 */ float sUnk274;         /* class 81: 5000, class 82: 1500 */
} MISSILE;

#endif
