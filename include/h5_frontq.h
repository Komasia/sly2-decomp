/* The front end's action queue (SafeHouse frontend.cpp: 0x1A4E08 starts the boot sequence, 0x1A4E80 runs the next
 * action at each world change): up to 16 actions of 0x1C bytes, run in order. Only the front end's (h5 range) files
 * use it. */
#ifndef H5_FRONTQ_H
#define H5_FRONTQ_H

/* action kinds */
#define ACTK_MOVIE        0   /* queue a movie (pbKey), then go to the boot world */
#define ACTK_MOVIE_F108   1   /* the same, the movie queue's +0x108 set */
#define ACTK_WORLD        2   /* a world transition (pbKey, oid, grf) */
#define ACTK_TASK         3   /* start a task by oid */
#define ACTK_NONE         4
#define ACTK_CARD         5   /* the memory card's messages on, then the next action */

struct ACTION {
    /* 0x00 */ unsigned int actk;
    /* 0x04 */ void *pbMovie;     /* ACTK_MOVIE: the movie's file key */
    /* 0x08 */ void *pbWorld;     /* ACTK_WORLD: the world's file key */
    /* 0x0c */ int oidWorld;      /* ACTK_WORLD: the warp target */
    /* 0x10 */ int grfWorld;      /* ACTK_WORLD: the request's flags */
    /* 0x14 */ int nTask;         /* ACTK_TASK */
    /* 0x18 */ int oidTask;       /* ACTK_TASK */
};

struct ACTIONQ {
    /* 0x000 */ unsigned int cact;
    /* 0x004 */ struct ACTION aact[16];
    /* 0x1c4 */ int iact;         /* the next action to run */
};

#endif
