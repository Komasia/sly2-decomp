/* Guard AI jobs of the 0x170000 module: JOBSCRIPT (runs a command list) and JOBINVESTIGATE (0xAB, investigates a
 * noise). Layout: the matched code, names after SafeHouse (aijobs.h JOBSCRIPT, ainoise.h JOBINVESTIGATE; field:
 * SafeHouse port). */
#ifndef H2_AIJOBS_H
#define H2_AIJOBS_H
#include "aijob.h"

#ifndef SLY2_QWORD
#define SLY2_QWORD
typedef int qword __attribute__((mode(TI)));
#endif

struct CMD;
struct CMDLIST;
struct SAVEDSCRIPT;

typedef struct JOBSCRIPT {
    /* 0x00 */ AIJOB aijob;
    /* 0x24 */ char unk_0x24[0x30 - 0x24];
    /* 0x30 */ struct CMDLIST *pcmdlist;
    /* 0x34 */ void *ploNear;           /* the object the commands are relative to */
    /* 0x38 */ struct CMD *pcmd;        /* the current command */
    /* 0x3c */ float tCmd;              /* when it started */
    /* 0x40 */ int fRunning;
    /* 0x44 */ struct SAVEDSCRIPT *psaved;
    /* 0x48 */ float radFace;
    /* 0x4c */ int fFromReact;
} JOBSCRIPT;

/* JOBINVESTIGATE states */
#define INVS_None       -1
#define INVS_Alerted     0
#define INVS_Going       1   /* going to the noise */
#define INVS_Looking     2   /* facing it, waiting */
#define INVS_Searching   3   /* searching around */
#define INVS_GivingUp    4
#define INVS_Paused      5   /* the game is paused */

typedef struct JOBINVESTIGATE {
    /* 0x00 */ AIJOB aijob;
    /* 0x24 */ char unk_0x24[0x30 - 0x24];
    /* 0x30 */ int st;
    /* 0x34 */ float tSt;
    /* 0x38 */ float tEnd;              /* when it gives up */
    /* 0x3c */ float tSearch;           /* when it starts searching around */
    /* 0x40 */ float t40;
    /* 0x44 */ struct NOISE *pnoise;
    /* 0x48 */ int fNew;                /* a new noise to follow */
    /* 0x4c */ int unk_0x4c;
    /* 0x50 */ qword aposWay[4][2];     /* the search's places: the goal, then the place it is near */
    /* 0xd0 */ int iway;
} JOBINVESTIGATE;

#endif
