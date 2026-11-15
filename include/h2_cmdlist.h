/* Command lists (CMDLIST, cid 0x71: a guard's script of commands) and the job running them (JOBSCRIPT, an AIJOB).
 * Layout: the matched code; names after SafeHouse (ai.h CMD / CMDLIST / SAVEDSCRIPT, aijobs.h JOBSCRIPT; field:
 * SafeHouse port). */
#ifndef H2_CMDLIST_H
#define H2_CMDLIST_H

/* command ops (SafeHouse ai.h CMD::op) */
#define CMDOP_Near      0   /* the object the next commands are relative to */
#define CMDOP_Range1    1
#define CMDOP_Range2    2
#define CMDOP_Look      3
#define CMDOP_Message   4
#define CMDOP_Wait      5   /* (SafeHouse: spawn / the wait g8) */
#define CMDOP_Path      6   /* move along a path */
#define CMDOP_Goto      7
#define CMDOP_Sound     8
#define CMDOP_Marker    9
#define CMDOP_Jump      10
#define CMDOP_Lock      11
#define CMDOP_Unlock    12
#define CMDOP_Job       13  /* a sub-job */
#define CMDOP_Anim      14
#define CMDOP_Alarm     15

typedef struct CMD {
    /* 0x00 */ int op;
    /* 0x04 */ int oid;
    /* 0x08 */ int n8;          /* by op: a word, a time, a point */
    /* 0x0c */ int nC;
    /* 0x10 */ int n10;
    /* 0x14 */ float g14;
    /* 0x18 */ struct CMD *pcmdNext;
} CMD;

/* a command list's saved place (the guard's +0x2DC) */
typedef struct SAVEDSCRIPT {
    /* 0x0 */ CMD *pcmd;
    /* 0x4 */ void *plo;
    /* 0x8 */ float g;
} SAVEDSCRIPT;

#endif
