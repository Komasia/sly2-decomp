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
    /* 0x64 */ struct TASK *ptaskFirst;   /* reaching it begins the job */
    /* 0x68 */ struct TASK *ptaskLast;    /* reaching it completes the job */
    /* 0x6c */ int idName;          /* its name / description strings */
    /* 0x70 */ int idDesc;
    /* 0x74 */ int unk_0x74;
    /* 0x78 */ int fNoClose;        /* completing it does not close its last task (nor auto-save) */
    /* 0x7c */ int cPlayed;
    /* 0x80 */ struct TASK *ptaskList;    /* a list of its tasks (linked through TASK +0x84) */
    /* 0x84 */ char unk_0x84[0x8c - 0x84];
    /* 0x8c */ int cobje;           /* at most 32 */
    /* 0x90 */ TASKOBJE *aobje;
    /* 0x94 */ int csme;            /* at most 32 */
    /* 0x98 */ TASKSME *asme;
    /* 0x9c */ float tSuckStart;    /* 480: the play time from which it grows the suck */
    /* 0xa0 */ float tSuckEnd;      /* 720 */
    /* 0xa4 */ float tElapsed;      /* the play time */
    /* 0xa8 */ void *pvA8;
    /* 0xac */ int oidScreen;       /* the screen object of the completion sequence */
    /* 0xb0 */ int idPartComplete;  /* its parts: sequence 1 (complete), 2 (next) */
    /* 0xb4 */ int idPartNext;
    /* 0xb8 */ void *ploScreen;     /* the object oidScreen (0: no sequence) */
    /* 0xbc */ void *ploScreen379;  /* the screen object 0x379 (sequence 3) */
    /* 0xc0 */ struct TASK *ptaskNext;    /* the next job's task (SetJobSeq) */
    /* 0xc4 */ int nSeq;            /* the completion sequence: 0 none, 1 complete, 2 next, 3 the next job */
    /* 0xc8 */ float tSeq;
    /* 0xcc */ void *ploExit;       /* an exit triggered at the end */
    /* 0xd0 */ PROGREF prPlayed;
    /* 0xd8 */ PROGREF prDone;
    /* 0xe0 */ PROGREF prElapsed;
    /* 0xe8 */ PROGREF prE8;
    /* 0xf0 */ int nMode;           /* the change's mode (2 / 3: no task updates) */
    /* 0xf4 */ void *ploContext;
} JOB;

/* a task (the LO part first) */
typedef struct TASK {
    /* 0x000 */ char unk_lo[0x54];
    /* 0x054 */ int nState;
    /* 0x058 */ float tState;       /* when the state changed */
    /* 0x05c */ int idDialog;
    /* 0x060 */ int fDialog;
    /* 0x064 */ int cPlayed;
    /* 0x068 */ int cDone;
    /* 0x06c */ int fPrereqAvailable;  /* as a prerequisite, available already counts */
    /* 0x070 */ int unk_0x70[2];
    /* 0x078 */ float dtLimit;
    /* 0x07c */ JOB *pjob;
    /* 0x080 */ void *ploShown;     /* present while the task is available */
    /* 0x084 */ struct TASK *ptaskNextJob;
    /* 0x088 */ struct TASK *ptaskNextAll;   /* all tasks (D_003E0F90) */
    /* 0x08c */ int unk_0x8c;
    /* 0x090 */ int *aoidPrereq;
    /* 0x094 */ int cptaskPrereq;
    /* 0x098 */ struct TASK **aptaskPrereq;
    /* 0x09c */ int *aoidNext;
    /* 0x0a0 */ int cptaskNext;
    /* 0x0a4 */ struct TASK **aptaskNext;
    /* 0x0a8 */ int cobje;
    /* 0x0ac */ TASKOBJE *aobje;
    /* 0x0b0 */ int csme;
    /* 0x0b4 */ TASKSME *asme;
    /* 0x0b8 */ int oidChk;         /* its checkpoint (the transition's point; -1 none) */
    /* 0x0bc */ int iwrec;          /* its world (-1: any) */
    /* 0x0c0 */ int oidPo;          /* the player character it starts with (-1: keep) */
    /* 0x0c4 */ void *ploExit;      /* an exit triggered when it activates */
    /* 0x0c8 */ PROGREF prPlayed;
    /* 0x0d0 */ PROGREF prCDone;
    /* 0x0d8 */ PROGREF prDone;
    /* 0x0e0 */ PROGREF prState;
    /* 0x0e8 */ PROGREF prRestart;
    /* 0x0f0 */ int nPending;       /* the state a change is taking it to (-1: none) */
    /* 0x0f4 */ int nMode;          /* the change's mode */
    /* 0x0f8 */ void *ploContext;
    /* 0x0fc */ int cVisit;         /* VisitTask */
    /* 0x100 */ int nDepth;
    /* 0x104 */ int nJobDepth;
} TASK;

#endif
