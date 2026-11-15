/* MC: the memory card manager (the game's save system, D_002E65E0 = g_save in SafeHouse frontend.h; Sly 1 save.c
 * SAVE), module 0x1AA978..0x1ACA*: the card's port and slot, the current and the wanted state (UpdateSave moves
 * one toward the other through func_001AB418), the three save slots (0x5464 bytes each: the save data, its card
 * directory entry at +0x5408) and the Sly 1 MEMCARD worker thread at +0xFD5C. Only the h5 range's memcard files use
 * this header. Layout: the code (InitSave 0x1AB128, UpdateSave 0x1AB1A0, 0x1AB418, 0x1AC598). */
#ifndef H5_MC_H
#define H5_MC_H

/* a save slot's card directory entry (filled from sceMcTblGetDir by FUN_0018b780; CompareSaves orders them) */
struct MCDIRENT {
    /* 0x00 */ char achName[0x44];
    /* 0x44 */ int cb;
    /* 0x48 */ unsigned short grfattr;
    /* 0x4a */ unsigned char dateCreate[8];
    /* 0x52 */ unsigned char dateModify[8];
    /* 0x5a */ char pad5A[0x5C - 0x5A];
};

struct MCSLOT {
    /* 0x0000 */ char abSave[0x5408];  /* the save data */
    /* 0x5408 */ struct MCDIRENT dirent;
};

struct MC {
    /* 0x0000 */ int port;
    /* 0x0004 */ int slot;
    /* 0x0008 */ int state;           /* the current state (-1 none) */
    /* 0x000c */ int stateWanted;     /* the state UpdateSave moves to */
    /* 0x0010 */ float tState;        /* when the state was set (g_clock.tReal) */
    /* 0x0014 */ float tPoll;         /* the next card check (g_clock.tReal) */
    /* 0x0018 */ int typeCard;        /* sceMcGetInfo: the card's type (2: a PS2 card) */
    /* 0x001c */ int cclusterFree;    /* sceMcGetInfo: the free space in 1 KB clusters */
    /* 0x0020 */ int fFormatted;      /* sceMcGetInfo: the card is formatted */
    /* 0x0024 */ struct MCSLOT aslot[3];
    /* 0xfd50 */ struct MCSLOT *pslotGame;  /* the slot the game plays and saves to (0: none) */
    /* 0xfd54 */ struct MCSLOT *pslotNewest; /* the newest slot with a game (state 6) */
    /* 0xfd58 */ struct MCSLOT *pslotChosen; /* a slot chosen for a new game (0x1ABC68 writes it fresh) */
    /* 0xfd5c */ char memcard[0x14];  /* MEMCARD (memcard.h): the worker thread */
};

/* the card states (MC::state / stateWanted), from sceMcGetInfo's results (func_001AC598) */
#define MCS_NONE        -1
#define MCS_NO_CARD      1  /* no card, or not a PS2 card */
#define MCS_UNFORMATTED  2
#define MCS_READY        3  /* formatted */
#define MCS_NO_SPACE     4  /* no save and too little room for one */
#define MCS_SAVES        5  /* the save directory read */
#define MCS_SLOTS        6  /* the slots validated, the newest chosen */

#define H5_MC_OFFSET(t, m) ((unsigned int)&(((t *)0)->m))
typedef char H5_MC_aslot[H5_MC_OFFSET(struct MC, aslot) == 0x24 ? 1 : -1];
typedef char H5_MC_pslotNewest[H5_MC_OFFSET(struct MC, pslotNewest) == 0xFD54 ? 1 : -1];
typedef char H5_MC_memcard[H5_MC_OFFSET(struct MC, memcard) == 0xFD5C ? 1 : -1];
typedef char H5_MCSLOT_size[sizeof(struct MCSLOT) == 0x5464 ? 1 : -1];

#endif
