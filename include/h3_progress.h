/* Sly 2 progress values (the saved game state): the progress layout every world file carries (a trie of PENT nodes
 * plus a name table, loaded by LoadProgressFromBrx 0x1D7B88 into D_003E0EA8) and the save block g_gamesave
 * (D_003D4A60, 0x5408 bytes: 0x5400 bytes of values, then the layout's identity at +0x5400 / +0x5404).
 * A value is found by a path (KEY: a list of symbols - names or numbers) walked down the trie (FFindEntryKey); an
 * indexed node takes the next path element as its index.
 * Layouts and names: SafeHouse port (Sly2-Release/savedata.h, savedata.cpp), checked against the matched code. */
#ifndef H3_PROGRESS_H
#define H3_PROGRESS_H

/* a trie node (10 bytes in the world file) */
typedef struct PENT {              /* field: SafeHouse port */
    /* 0x0 */ short ch;            /* the path element's symbol */
    /* 0x2 */ signed char kind;    /* PROGK */
    /* 0x3 */ unsigned char fIndexed;   /* the next path element indexes it (bools: the bit count) */
    /* 0x4 */ unsigned short ib;   /* the value's offset in the save */
    /* 0x6 */ unsigned short iChild;
    /* 0x8 */ unsigned short iSibling;
} PENT;

/* value kinds (PENT.kind) */
#define PROGK_Node -1              /* inner node, no value */
#define PROGK_S32 0                /* 0, 1, 2, 9 and 10 are all one 32-bit int */
#define PROGK_S32_1 1
#define PROGK_S32_2 2
#define PROGK_F32 3
#define PROGK_Bool 4               /* a byte, or bits when indexed */
#define PROGK_Vector 5
#define PROGK_S32x4 6
#define PROGK_S32x2 7
#define PROGK_S32x3 8
#define PROGK_S32_9 9
#define PROGK_S32_10 10

/* a progress path: its symbols */
typedef struct KEY {
    /* 0x0 */ int csym;
    /* 0x4 */ unsigned short *asym;
} KEY;

/* the result of a trie walk: the node and the index taken by an indexed node */
typedef struct PENTFOUND {
    /* 0x0 */ PENT *pent;
    /* 0x4 */ int i;
} PENTFOUND;

/* the layout's name table: symbol names hashed (h * 33 + toupper, func_001D8640) into 53 buckets */
#define CNAMEBUCKET 0x35
typedef struct NAME {
    /* 0x0 */ unsigned int h;
    /* 0x4 */ char *pchz;
    /* 0x8 */ int sym;
    /* 0xc */ struct NAME *pnameNext;
} NAME;
typedef struct NAMETABLE {
    /* 0x00 */ NAME *apname[CNAMEBUCKET];
    /* 0xd4 */ int cnameFree;      /* entries of the pool still free (used from the end) */
    /* 0xd8 */ NAME *anamePool;
} NAMETABLE;

/* the progress layout of the loaded world (SafeHouse LAYOUT) */
typedef struct LAYOUT {
    /* 0x0 */ int cent;
    /* 0x4 */ PENT *aent;          /* aent[0] is the root */
    /* 0x8 */ NAMETABLE nametable;
} LAYOUT;

#define CB_GAMESAVEVALUES 0x5400
typedef struct GAMESAVE {
    /* 0x0000 */ unsigned char ab[CB_GAMESAVEVALUES];
    /* 0x5400 */ int nLayout;      /* the layout's identity: its last record's ib */
    /* 0x5404 */ int sumLayout;    /* and the byte sum of its records */
} GAMESAVE;

#endif
