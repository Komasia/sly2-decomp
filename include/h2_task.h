/* Jobs (cid 0x84) and tasks (cid 0x85) and their records, for the task module 0x161478..0x166270. Layout: the
 * matched code, names after SafeHouse (task.h JOB / TASK / TASKOBJE / TASKSME, task.cpp: field: SafeHouse port).
 * A task's state: -1 none, 0 locked, 1 available, 2 done, 3 done and closed; 4 / 5 name the "start" / "end" object
 * groups of ApplyTaskObjects. */
#ifndef H2_TASK_H
#define H2_TASK_H

/* task states */
#define TASKS_None      -1
#define TASKS_Locked     0
#define TASKS_Available  1
#define TASKS_Done       2
#define TASKS_Closed     3
#define TASKS_Start      4
#define TASKS_End        5

/* an object shown in some states (JOB / TASK aobje): added in the states of grfState, removed in the others */
typedef struct TASKOBJE {
    /* 0x0 */ int oid;          /* the object */
    /* 0x4 */ int oidOwner;     /* its owner (-1: global) */
    /* 0x8 */ int grfState;     /* 1 << state (func_00161FC8) */
    /* 0xc */ int iwrec;        /* only in this world (-1: any) */
} TASKOBJE;

/* an object's state-machine goal for a state (JOB / TASK asme) */
typedef struct TASKSME {
    /* 0x00 */ int nState;      /* -1: any, the goal by the state (0x612..0x615) */
    /* 0x04 */ int oid;         /* the object with the state machine */
    /* 0x08 */ int oidSm;       /* its state machine */
    /* 0x0c */ int oidGoal;     /* the goal (-1: none) */
    /* 0x10 */ int fNotInstant; /* skipped by an instant change (mode 0) */
    /* 0x14 */ int iwrec;       /* only in this world (-1: any) */
} TASKSME;

/* a progress reference: a progress path (NProgress reads it, when set) */
typedef struct PROGREF {
    /* 0x0 */ int ckey;
    /* 0x4 */ void *akey;
} PROGREF;

/* a job (the LO part first) */
typedef struct JOB {
    /* 0x00 */ char unk_lo[0x50];
    /* 0x50 */ int fDisabled;       /* SafeHouse f50: when set the job does nothing */
    /* 0x54 */ int cnEndClose;      /* events that close the job (at most 32) */
    /* 0x58 */ int *anEndClose;
    /* 0x5c */ int cnEnd;           /* events that end it (at most 32) */
    /* 0x60 */ int *anEnd;
    /* 0x64 */ char unk_0x64[0x7c - 0x64];
    /* 0x7c */ int cPlayed;
    /* 0x80 */ struct TASK *ptaskFirst;   /* its tasks (TASK::ptaskNext) */
    /* 0x84 */ char unk_0x84[0x8c - 0x84];
    /* 0x8c */ int cobje;           /* at most 32 */
    /* 0x90 */ TASKOBJE *aobje;
    /* 0x94 */ int csme;            /* at most 32 */
    /* 0x98 */ TASKSME *asme;
    /* 0x9c */ float tSuckStart;    /* 480: the play time from which it grows the suck */
    /* 0xa0 */ float tSuckEnd;      /* 720 */
    /* 0xa4 */ float tElapsed;      /* the play time */
    /* 0xa8 */ void *pvA8;
    /* 0xac */ int oidAC;
    /* 0xb0 */ int nB0;
    /* 0xb4 */ int nB4;
    /* 0xb8 */ void *ploB8;         /* the object oidAC */
    /* 0xbc */ void *ploBC;         /* the object 0x379 */
    /* 0xc0 */ char unk_0xc0[0xd0 - 0xc0];
    /* 0xd0 */ PROGREF prPlayed;
    /* 0xd8 */ PROGREF prD8;
    /* 0xe0 */ PROGREF prElapsed;
    /* 0xe8 */ PROGREF prE8;
    /* 0xf0 */ int nMode;           /* the change's mode (2 / 3: no task updates) */
} JOB;

#endif
