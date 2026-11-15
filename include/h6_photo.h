/* PHOTOTARGET (cid 0x2E, derived from XFM): a target the binocucom's photo prompt can take a picture of, with the task
 * that the photo completes. Layout after SafeHouse's photo.cpp (field: SafeHouse port). */
#ifndef H6_PHOTO_H
#define H6_PHOTO_H

/* only the task's state is used here */
typedef struct PHOTOTASK {
    /* 0x00 */ char pad0[0x54];
    /* 0x54 */ int nState;            /* 1 open, 2 done */
} PHOTOTASK;

typedef struct PHOTOTARGET {
    /* 0x000 */ char pad0[0x28];
    /* 0x028 */ unsigned long grfLo;   /* the LO flag qword (bit 60: in the world) */
    /* 0x030 */ char pad30[0xB0];
    /* 0x0e0 */ float radius;          /* 75 by default */
    /* 0x0e4 */ float size;            /* height of the size marker (0 = radius) */
    /* 0x0e8 */ float tolerance;       /* how far below full size still counts (0.25) */
    /* 0x0ec */ PHOTOTASK *ptask;      /* task the photo completes */
    /* 0x0f0 */ int fDone;             /* the photo was taken (no task) */
    /* 0x0f4 */ int title;
    /* 0x0f8 */ int listTitle;         /* -2 = title */
    /* 0x0fc */ int dialog;
    /* 0x100 */ struct PHOTOTARGET *ploLinked;   /* an LO shown only while the target is not in the world */
    /* 0x104 */ float radiusLinked;    /* 5000 by default */
    /* 0x108 */ int visibility;
    /* 0x10c */ int fCustom;           /* show the message instead of taking the photo */
    /* 0x110 */ int message;
} PHOTOTARGET;

/* the LO flag qword's bit 60 */
#define FPhotoTargetInWorld(ptarget) ((int)((ptarget)->grfLo >> 60) & 1)

#endif
