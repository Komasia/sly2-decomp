/* WR (class 115, derived from LO; Sly 1 wr.c "warp"): up to eight warp entries, each a circle or bend warp, and the
 * noise used to animate them. Partial layout from the matched Sly 2 code; Sly 2's LO is 0x50 bytes (Sly 1: 0x34). */
#ifndef WR_H
#define WR_H
#include "so.h"
#include "util.h"

enum WREK { WREK_Nil = -1, WREK_Circle = 0, WREK_Bend = 1, WREK_Max = 2 };

#ifndef ENSK_DEFINED
#define ENSK_DEFINED
typedef enum ENSK { ENSK_Get = 0, ENSK_Set = 1 } ENSK;
#endif

/* one noise component */
typedef struct ONZE {
    float uAmpl;
    float gFreq;
    float gPhase;
    float uRandom;
} ONZE;

/* sum of up to four noise components */
typedef struct ONZ {
    /* 0x00 */ LM lm;
    /* 0x08 */ float uBias;
    /* 0x0c */ uint conze;
    /* 0x10 */ ONZE aonze[4];
} ONZ;

typedef struct WRE {
    /* 0x00 */ enum WREK wrek;
    /* 0x04 */ int imat;
    /* 0x08 */ char unk_0x08[0xd0 - 0x08];
} WRE;

typedef struct WR {
    /* 0x000 */ LO lo;
    /* 0x050 */ float tLastUpdate;
    /* 0x054 */ int cwre;
    /* 0x058 */ int cmat;
    /* 0x05c */ int imatHalf;
    /* 0x060 */ WRE awre[8];
    /* 0x6e0 */ int iwreCur;
    /* 0x6e4 */ char unk_0x6e4[0x8fc - 0x6e4];
    /* 0x8fc */ int fValuesChanged;
} WR;

#endif
