/* SPAWNER (cid 0x77, CID_SPAWNER): spawns guards from proxies at sources (proxies, paths, points) out of the camera's
 * view. Layout: the matched code, names after SafeHouse (spawner.cpp SOURCE / SLOT / SPAWNER; field: SafeHouse
 * port). */
#ifndef H2_SPAWNER_H
#define H2_SPAWNER_H

#ifndef SLY2_QWORD
#define SLY2_QWORD
typedef int qword __attribute__((mode(TI)));
#endif

/* source kinds */
#define SRCK_Proxy  0
#define SRCK_Path   1   /* a path: its own command list, a move along it */
#define SRCK_Point  2

typedef struct SOURCE {
    /* 0x00 */ int kind;
    /* 0x04 */ int oid;
    /* 0x08 */ void *plo;
    /* 0x0c */ void *plist;         /* kind 1: its command list */
    /* 0x10 */ int pcmdPath;        /* kind 1: the list's (one) command */
    /* 0x14 */ int fBusy;
    /* 0x18 */ float tUntil;
} SOURCE;   /* 0x1C bytes */

typedef struct SLOT {
    /* 0x00 */ void *plo;           /* the guard */
    /* 0x04 */ float tTime;
    /* 0x08 */ float tWait;
    /* 0x0c */ SOURCE *psrc;
    /* 0x10 */ int k;
    /* 0x14 */ int unk_0x14[3];
    /* 0x20 */ qword pos;
} SLOT;     /* 0x30 bytes */

typedef struct SPAWNER {
    /* 0x00 */ char unk_lo[0x40];
    /* 0x40 */ unsigned int grfUpd;     /* LO +0x40: the update flags, or a pointer to them (bit 0 clear) */
    /* 0x44 */ char unk_0x44[0x50 - 0x44];
    /* 0x50 */ int csrc;                /* at most 0x80 */
    /* 0x54 */ SOURCE *asrc;
    /* 0x58 */ int cUsed;
    /* 0x5c */ int cslot;
    /* 0x60 */ SLOT *aslot;
    /* 0x64 */ char unk_0x64[0x70 - 0x64];
    /* 0x70 */ qword posLast;
    /* 0x80 */ float sPlanar;           /* 5500 */
    /* 0x84 */ int fEdge;
    /* 0x88 */ int fRange;
    /* 0x8c */ int fOcclusion;
    /* 0x90 */ int coidProxy;           /* at most 8 */
    /* 0x94 */ int *aoidProxy;
    /* 0x98 */ int cpos;                /* at most 16 */
    /* 0x9c */ qword *apos;
    /* 0xa0 */ float dtWaitFar;         /* 30 */
    /* 0xa4 */ float dtUntilFar;        /* 50 */
    /* 0xa8 */ float tNext;
    /* 0xac */ int nMode;
} SPAWNER;

#endif
