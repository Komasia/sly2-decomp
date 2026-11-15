/* EPMENU: the front end's episode menu (class 0x83, a screen object; the one menu is D_003E1C04). The fields from
 * +0x110 on: SafeHouse port (frontend.cpp EPMENU). Its tables in the executable, indexed by episode (0 the movies,
 * 1..8 the episodes): D_002BE080 / D_002BE1B8 the parts per mode, D_002BE248 the episode's movie, D_002BE2D0 the
 * movie counts. */
#ifndef H2_EPMENU_H
#define H2_EPMENU_H

/* modes (SafeHouse frontend.cpp) */
#define EPMODE_None     -1
#define EPMODE_Start     0
#define EPMODE_Select    2      /* choosing an episode */
#define EPMODE_Next      4      /* moving down to next */
#define EPMODE_Prev      6      /* moving up to next */
#define EPMODE_Confirm   7
#define EPMODE_Movies    8      /* the movie list (sub 0: idle, 1 / 2: stepping) */
#define EPMODE_Back      9
#define EPMODE_Enter    10      /* enter the current episode */

typedef struct EPMENU {
    /* 0x000 */ char unk_0x000[0x110];   /* the screen object */
    /* 0x110 */ int cur;           /* the episode shown (0: the movies) */
    /* 0x114 */ int next;          /* the episode being moved to */
    /* 0x118 */ int max;           /* the last episode open */
    /* 0x11c */ int mode;
    /* 0x120 */ int sub;
    /* 0x124 */ float tMode;       /* g_clock.tReal when the mode was set */
    /* 0x128 */ int imovie;        /* the movie chosen (cur 0) */
    /* 0x12c */ int hint;          /* the "view the movie" hint: -1 none, 0 off, 1 shown */
    /* 0x130 */ float tHint;       /* g_clock.tReal when the hint changed */
} EPMENU;

/* the world's per-episode progress keys (SW +0x3B58): "episode/<name>/dt" and "episode/<name>/percent_complete" */
typedef struct SWEPPROGRESS {
    void *apvDt[9];
    void *apvPercent[9];
} SWEPPROGRESS;

#endif
